#include "../my_chat.h"
#include <stdio_ext.h>

extern struct User me;
extern pthread_mutex_t screen;

void message_create_thread(mqd_t *write_mqds) {
    WINDOW *main_win, *print_win, *help_win;
    char buffer[256], *message;
    int x, y;
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
    noecho();
    wprintw(print_win, "Press Enter!");
    wrefresh(print_win);


    wscanw(print_win, "%s", buffer);
    wclear(print_win);
    curs_set(1);
    echo();
    wrefresh(print_win);
    box(main_win, 0, 0);
    wrefresh(main_win);
    memset(buffer, 0, 256);
    strncat(buffer, me.nickname, strlen(me.nickname));
    strncat(buffer, ":", 2);
    message = &buffer[strlen(buffer)];

    while (1) {
        memset(message, 0, 256 - strlen(buffer));
        wgetnstr(print_win, message, 255 - strlen(buffer));
        wclear(print_win);
        wrefresh(print_win);
        if (strcmp(message, "exit") == 0) {
            mq_send(*write_mqds, (char *) &me, 256, DELETED_USER);
            pthread_mutex_lock(&screen);
            delwin(print_win);
            delwin(main_win);
            delwin(help_win);
            pthread_mutex_unlock(&screen);
            pthread_exit(NULL);
        } else if (mq_send(*write_mqds, buffer, 256, MESSAGE) == -1)
            errExit("mq_send message error!\n");
    }
}