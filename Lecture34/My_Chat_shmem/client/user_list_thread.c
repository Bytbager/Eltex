#include "../my_chat_shmem.h"

struct user *user;
extern struct user me;

/*Функция представляет собой start_routine потока,
который отвечает за вывод списка пользователей*/
void user_list_thread() {
    WINDOW *main_win, *print_win;    
    struct args clean_args;

    int key_shm, key_sem, fd_shm, fd_sem, shm_id, sem_id;
    struct sembuf lock[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};
    struct shmid_ds shm_stat;
    time_t last_atime = 0, last_dtime = 0;

    /*Создаём окна:
    main_win - отображает границы окна
    print_win - окно, в котором будет отображаться печать пользователя*/

    int x, y;
    getmaxyx(curscr, y, x);
    main_win = newwin(35, 20, 0, 0);
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

    key_shm = ftok(SHMEM_USER, PROJ_ID);
    if (key_shm == -1)
        errExit("ftok users_thread error!\n");
    shm_id = shmget(key_shm, 20 * sizeof(struct user), 0666);
    if (shm_id == -1)
        errExit("shmget users_thread error!\n");

    /*Подключаемся к семафору*/

    key_sem = ftok(SEMAPHORE_USERS, PROJ_ID);
    if (key_sem == -1)
        errExit("ftok users_thread error!\n");
    sem_id = semget(key_sem, 1, 0666);
    if (sem_id == -1)
        errExit("semget users_thread error!\n");

    /*Получаем указатель на память и заполняем структуру shmid_ds
    с помощью shmctl IPC_STAT из неё нам нужны параметры shm_atime
    и shm_dtime, по ним клиент будет понимать о поступлении нового пользователя*/

    if (semop(sem_id, lock, 2) == -1)
        errExit("semop user_list_thread lock error!\n");

    user = shmat(shm_id, NULL, 0666);
    if (user == ((void *) -1))
        errExit("shmat users_thread error!\n");

    if (shmctl(shm_id, IPC_STAT, &shm_stat) == -1)
        errExit("shmctl ipc_stat error!\n");
        last_atime = shm_stat.shm_atime;
        last_dtime = shm_stat.shm_dtime;

    for (int i = 0; i < 20; i++) {
        if (user[i].pid == 0) {
            user[i].pid = me.pid;
            strncat(user[i].nickname, me.nickname, strlen(me.nickname) + 1);
            break;
        }
    }

    for (int i = 0; i < 20; i++)
        if (user[i].pid != 0)
            wprintw(print_win, "%s\n", user[i].nickname);
    wrefresh(print_win);

    clean_args.main_win = main_win;
    clean_args.print_win = print_win;
    clean_args.user = user;    

    /*Данный поток будет завершаться с помощью pthread_cancel,
    поэтому нужно указать функцию и аргументы для очистки ресурсов*/

    pthread_cleanup_push(cleanup_thread, (void *) &clean_args);

    if (semop(sem_id, &unlock, 1) == -1)
        errExit("semop user_list_thread unlock error!\n");

    /*Входим в бесконечный цикл
    В нём каждую секунду проверяем параметр shm_atime 
    и shm_dtime, если какой-либо из них поменялся,
    значит новый клиент выполнил функцию shmat или shmdt
    для данного сегмента памяти. В таком случае выводим новый
    список пользователей*/

    while (1) {
        sleep(1);
        if (shmctl(shm_id, IPC_STAT, &shm_stat) == -1)
            errExit("shmctl ipc_stat error!\n");
        if (me.pid == shm_stat.shm_lpid) {
            continue;
        }
        else if (last_atime != shm_stat.shm_atime || last_dtime != shm_stat.shm_dtime) {
            if (semop(sem_id, lock, 2) == -1)
                errExit("semop lock user_list_thread error!\n");
            wclear(print_win);
            for (int i = 0; i < 20; i++)
                if (user[i].pid != 0)
                wprintw(print_win, "%s\n", user[i].nickname);
            wrefresh(print_win);
            if (semop(sem_id, &unlock, 1) == -1)
                errExit("semop unlock user_list_thread error!\n");
        }
    }

    pthread_cleanup_pop(0);
}