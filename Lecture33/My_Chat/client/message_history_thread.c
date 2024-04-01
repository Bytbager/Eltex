#include "../my_chat.h"

extern pthread_mutex_t screen;

void message_history_thread(int *read_pipe) {
    WINDOW *main_win, *print_win;
    char *buffer;
    int x, y;

    pthread_mutex_lock(&screen);
    buffer = calloc(256, 1);
    if (buffer == NULL)
        errExit("buffer calloc error!\n");
    pthread_mutex_unlock(&screen);

    /*Создаём окна:
    main_win - отображает границы окна
    print_win - окно, в котором будет отображаться печать пользователя*/
    
    main_win = newwin(35, COLS - 21, 0, 22);
    wattron(main_win, COLOR_PAIR(1));
    box(main_win, 0, 0);
    wbkgd(main_win, COLOR_PAIR(1));
    wrefresh(main_win);

    getmaxyx(main_win, y, x);
    print_win = derwin(main_win, y - 2, x - 2, 1, 1);
    wattron(print_win, COLOR_PAIR(1));
    wbkgd(print_win, COLOR_PAIR(1));
    wrefresh(print_win);

    /*Входим в бесконечный цикл для получения новых сообщений*/
    while (1) {
        memset(buffer, 0, 256);

        /*Ожидаем сообщение от нашего главного потока в канале*/
        if (read(*read_pipe, buffer, 256) == -1)
            errExit("read message_hist_thread error!");

        /*Проверяем, не вышел ли наш пользователь из программы
        Для этого приводим буффер сообщения к типу (struct User *)
        и смотрим значение дескриптора, если пользователь вышел,
        наш главный поток запишет туда значение SERVER_RECEIVED_DELETION_REQUEST,
        в таком случае закрываем окна, очищаем буффер и завершаем поток*/
        if (((struct User *)buffer)->mqds == SERVER_RECEIVED_DELETION_REQUEST) {
            pthread_mutex_lock(&screen);
            delwin(print_win);
            delwin(main_win);
            free(buffer);
            pthread_mutex_unlock(&screen);
            pthread_exit(NULL);
        }

        /*Если пользователь не вышел, то просто выводим
        полученное сообщение на экран*/
        pthread_mutex_lock(&screen);
        wprintw(print_win, "%s\n", buffer);
        wrefresh(print_win);
        pthread_mutex_unlock(&screen);
    }
}