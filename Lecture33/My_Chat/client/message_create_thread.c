#include "../my_chat.h"


void message_create_thread(mqd_t *write_mqds) {
    WINDOW *main_win, *print_win;
    char buffer[256];
    int x, y;

    main_win = newwin(LINES - 37, COLS - 2, 37, 0);
    // wattron(main_win, COLOR_PAIR(1));
    box(main_win, 0, 0);
    // wbkgd(main_win, COLOR_PAIR(1));
    wrefresh(main_win);
    
    getmaxyx(main_win, y, x);
    print_win = derwin(main_win, y - 2, x - 2, 1, 1);
    // wattron(print_win, COLOR_PAIR(1));
    // wbkgd(print_win, COLOR_PAIR(1));
    keypad(print_win, TRUE);
    wrefresh(print_win);

    char button = 0;

    memset(buffer, 0, 256);
    int i = 0;
    while (1) {
        // fflush(stdin);
        // flushinp();
        // wclear(print_win);
        // wrefresh(print_win);
        wgetnstr(print_win, buffer, 255);
        wclear(print_win);
        wrefresh(print_win);
        if (mq_send(*write_mqds, buffer, 256, 1) == -1)
            errExit("mq_send message error!\n");
    }
}