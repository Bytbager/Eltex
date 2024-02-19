#include "../my_chat.h"

int start_screen(mqd_t ctosDS) {
    WINDOW *boxwin;
    WINDOW *textwin;
    struct User me;
    int y, x;
    me.pid = getpid();
    getmaxyx(stdscr, y, x);
    boxwin = newwin(y / 5, x / 5, y / 5 * 2, x / 5 * 2);
    box(boxwin, 0, 0);
    wrefresh(boxwin);
    textwin = derwin(boxwin, y / 5 - 2, x / 5 - 2, 1, 1);
    mvwprintw(textwin, 1, x / 15 - 2, "Enter your nickname:");
    wrefresh(textwin);
    mvwgetstr(textwin, 3, x / 15 - 2, me.nickname);
    if (mq_send(ctosDS, (char *)&me, sizeof(me), 32) == -1)
        errExit("mq_send error\n");
    return 0;
}