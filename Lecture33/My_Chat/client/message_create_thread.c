#include "../my_chat.h"
#include <stdio_ext.h>

extern struct User me;
extern pthread_mutex_t screen;

void message_create_thread(mqd_t *write_mqds) {
    WINDOW *main_win, *print_win, *help_win;
    char buffer[256], *message;
    int x, y;

    /*Создаём окна:
    help_win - отображает надпись о том, как выйти из чата
    main_win - отображает границы окна
    print_win - окно, в котором будет отображаться печать пользователя*/

    help_win = newwin(1, COLS, 36, 0);
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
    keypad(print_win, TRUE);

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
    strncat(buffer, ":", 2);
    message = &buffer[strlen(buffer)];

    /*Входим в бесконечный цикл для ввода сообщений*/
    while (1) {
        memset(message, 0, 256 - strlen(buffer));
        wgetnstr(print_win, message, 255 - strlen(buffer));
        wclear(print_win);
        wrefresh(print_win);

        /*Если пользователь вводит "exit", отправляем серверу
        уведомление о выходе нашего пользователя, закрываем окна
        и завершаем поток*/
        if (strcmp(message, "exit") == 0) {
            mq_send(*write_mqds, (char *) &me, 256, DELETED_USER);
            pthread_mutex_lock(&screen);
            delwin(print_win);
            delwin(main_win);
            delwin(help_win);
            pthread_mutex_unlock(&screen);
            pthread_exit(NULL);
        }
        
        /*Если пользователь вводит любой другой текст, мы отправляем его
        серверу, он отправляет наше сообщение всем другим клиентам*/
        else if (mq_send(*write_mqds, buffer, 256, MESSAGE) == -1)
            errExit("mq_send message error!\n");
    }
}