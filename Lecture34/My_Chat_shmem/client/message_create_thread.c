#include "../my_chat_shmem.h"

extern struct user *user;
extern struct user me;
extern int shm_id, sem_id;

/*Функция представляет собой start_routine потока,
который отвечает за ввод сообщений*/
void message_create_thread() {
    WINDOW *main_win, *print_win, *help_win;
    char buffer[256], *message;
    int x, y;

    struct sembuf lock[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};
    char *msg_buffer;
    struct shmid_ds shm_stat;
    memset(&shm_stat, 0, sizeof(struct shmid_ds));

    /*Создаём окна:
    help_win - отображает надпись о том, как выйти из чата
    main_win - отображает границы окна
    print_win - окно, в котором будет отображаться печать пользователя*/

    getmaxyx(curscr, y, x);
    help_win = newwin(1, x - 3, 36, 0);
    wattron(help_win, COLOR_PAIR(1) | A_REVERSE);
    wbkgd(help_win, COLOR_PAIR(1) | A_REVERSE);
    wprintw(help_win, "Type \"exit\" if you want to close program");
    wrefresh(help_win);

    main_win = newwin(LINES - 38, COLS - 2, 38, 0);
    wattron(main_win, COLOR_PAIR(1));
    box(main_win, 0, 0);
    wbkgd(main_win, COLOR_PAIR(1));
    wrefresh(main_win);
    
    getmaxyx(main_win, y, x);
    print_win = derwin(main_win, y - 2, x - 2, 1, 1);
    wattron(print_win, COLOR_PAIR(1));
    wbkgd(print_win, COLOR_PAIR(1));

    /*Для удаления атрефактов в окне print_win вызываем noecho()
    и печатаем подсказку для пользователя*/

    noecho();
    wprintw(print_win, "Press Enter!");
    wrefresh(print_win);

    /*Далее собираем символы из потока ввода с помощью wscanw
    и очищаем окно*/

    wscanw(print_win, "%s", buffer);
    wclear(print_win);
    curs_set(1);
    echo();
    wrefresh(print_win);
    box(main_win, 0, 0);
    wrefresh(main_win);

    /*В начало буффура сообщений добавляем ник пользователя
    Записывать само сообщение будем после ника с помощью указателя
    message, он будет указывать на ячейку буффера buffer[strlen(buffer)]*/

    memset(buffer, 0, 256);
    strncat(buffer, me.nickname, strlen(me.nickname));
    strncat(buffer, ": ", 3);
    message = &buffer[strlen(buffer)];

    /*Далее получаем структуру shmid_ds для дальнейшей работы с ней.
    Подключение к семафору и сегменту памяти производилось в потоке,
    который отвечает за вывод истории сообщений.
    В данном потоке мы работаем с семафором и памятью с помощью глобальных переменных*/

    if (semop(sem_id, lock, 2) == -1)
        errExit("semop lock msg_create_thread error\n");

    msg_buffer = shmat(shm_id, NULL, 0666);
    if (msg_buffer == ((void *) -1))
        errExit("shmat message_create_thread error!\n");

    if (shmctl(shm_id, IPC_STAT, &shm_stat) == -1)
        errExit("shmctl msg_create_thread error!\n");

    if (semop(sem_id, &unlock, 1) == -1)
        errExit("semop unlock msg_create_thread error\n");    

    /*Входим в бесконечный цикл ввода сообщений*/

    while (1) {
        memset(message, 0, 256 - strlen(buffer));
        wclear(print_win);
        wrefresh(print_win);

        /*Вводим сообщение, далее проверяем текст в нём*/

        wgetnstr(print_win, message, 255 - strlen(buffer));

        /*Если текст "exit", удаляем себя из списка пользователей,
        удаляем окна и завершаем поток*/

        if (strcmp(message, "exit") == 0) {
            if (semop(sem_id, lock, 2) == -1)
                errExit("semop lock msg_create_thread error\n");

            for (int i = 0; i < 20; i++)
                if (user[i].pid == me.pid)
                    memset(&user[i], 0, sizeof(struct user));

            if (semop(sem_id, &unlock, 1) == -1)
                errExit("semop unlock msg_create_thread error\n");            
            delwin(print_win);
            delwin(main_win);
            delwin(help_win);
            pthread_exit(NULL);
        }
        
        /*Если пользователь ввел любой другой текст,
        то мы добавляем его в список сообщений и
        вызываем shmctl с параметром cmd IPC_SET.
        Таким образом мы обновляем значение shm_ctime в
        структуре shmid_ds для всех пользователей сегмента
        разделяемой памяти.
        С помощью этого механизма другие клиенты чата
        могут понять, что появилось новое сообщение и вывести
        его на экран*/
        
        else {
            if (semop(sem_id, lock, 2) == -1)
                errExit("semop lock msg_create_thread error\n");

            strncat(msg_buffer, buffer, strlen(buffer) + 1);
            strncat(msg_buffer, "\n", 2);

            if (shmctl(shm_id, IPC_SET, &shm_stat) == -1)
                errExit("shmctl msg_create_thread error!\n");

            if (semop(sem_id, &unlock, 1) == -1)
                errExit("semop unlock msg_create_thread error\n");    
        }

    }

}