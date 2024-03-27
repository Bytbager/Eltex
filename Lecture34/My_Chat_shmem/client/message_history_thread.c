#include "../my_chat_shmem.h"

int shm_id, sem_id;

/*Функция представляет собой start_routine потока,
который отвечает за вывод истории сообщений*/
void message_history_thread() {
    WINDOW *main_win, *print_win;
    struct args clean_args;
    int x, y;
    
    int key_shm, key_sem;
    struct sembuf lock[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};
    char *msg_buffer;
    struct shmid_ds shm_stat;
    time_t last_ctime;

    /*Создаём окна:
    main_win - отображает границы окна
    print_win - окно, в котором будет отображаться печать пользователя*/

    getmaxyx(curscr, y, x);
    main_win = newwin(35, x - 24, 0, 22);
    wattron(main_win, COLOR_PAIR(1));
    box(main_win, 0, 0);
    wbkgd(main_win, COLOR_PAIR(1));
    wrefresh(main_win);

    getmaxyx(main_win, y, x);
    print_win = derwin(main_win, y - 2, x - 2, 1, 1);
    wattron(print_win, COLOR_PAIR(1));
    wbkgd(print_win, COLOR_PAIR(1));
    wrefresh(print_win);

    /*Подключаемся к сегменту разделяемой памяти*/

    key_shm = ftok(SHMEM_MSG, PROJ_ID);
    if (key_shm == -1)
        errExit("ftok message_hist_thread error!\n");
    shm_id = shmget(key_shm, 2048, 0666);
    if (shm_id == -1)
        errExit("shmget message_hist_thread error!\n");

    /*Подключаемся к семафору*/

    key_sem = ftok(SEMAPHORE_MSG, PROJ_ID);
    if (key_sem == -1)
        errExit("ftok message_hist_thread error!\n");
    sem_id = semget(key_sem, 1, 0666);
    if (sem_id == -1)
        errExit("semget message_hist_thread error!\n");

    /*Получаем указатель на память и заполняем структуру shmid_ds
    с помощью shmctl IPC_STAT из неё нам нужен shm_ctime,
    по нему клиент будет понимать о поступлении нового сообщения*/

    if (semop(sem_id, lock, 2) == -1)
        errExit("semop user_list_thread lock error!\n");

    msg_buffer = shmat(shm_id, NULL, 0666);
    if (msg_buffer == ((void *) -1))
        errExit("shmat message_hist_thread error!\n");

    if (shmctl(shm_id, IPC_STAT, &shm_stat) == -1)
        errExit("shmctl ipc_stat error!\n");
        last_ctime = shm_stat.shm_ctime;

    wclear(print_win);
    wprintw(print_win, "%s", msg_buffer);
    wrefresh(print_win);

    clean_args.main_win = main_win;
    clean_args.print_win = print_win;
    clean_args.user = msg_buffer;

    /*Данный поток будет завершаться с помощью pthread_cancel,
    поэтому нужно указать функцию и аргументы для очистки ресурсов*/

    pthread_cleanup_push(cleanup_thread, &clean_args);

    if (semop(sem_id, &unlock, 1) == -1)
        errExit("semop user_list_thread unlock error!\n");

    /*Входим в бесконечный цикл
    В нём каждую секунду проверяем параметр shm_ctime,
    если он изменился относительно предыдущего - выводим
    список сообщений из сегмента разделяемой памяти*/

    while (1) {
        sleep(1);
        if (shmctl(shm_id, IPC_STAT, &shm_stat) == -1)
            errExit("shmctl ipc_stat error!\n");
        if (last_ctime != shm_stat.shm_ctime) {
            if (semop(sem_id, lock, 2) == -1)
                errExit("semop lock msg_hist_thread error!\n");
            wclear(print_win);
            wprintw(print_win, "%s", msg_buffer);
            wrefresh(print_win);
            if (semop(sem_id, &unlock, 1) == -1)
                errExit("semop unlock msg_hist_thread error!\n");
        }
    }

    pthread_cleanup_pop(0);
}