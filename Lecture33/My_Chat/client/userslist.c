#include "../my_chat.h"

extern pthread_cond_t userlist_cond;

void userlist(void) {
    mqd_t users_mq;
    WINDOW *userswin;
    WINDOW *usersderwin;
    int y, x;
    char **users = malloc(sizeof(char *));
    users[0] = malloc(128);
    char *msgbuffer = malloc(128);
    users_mq = mq_open(USERS_MQ, O_RDONLY);
    if (users_mq == -1)
        errExit("mq_open rdonly users_mq error\n");
    getmaxyx(stdscr, y, x);
    userswin = newwin(y, x - x / 10 * 8, 0, x / 10 * 8);
    box(userswin, 0, 0);
    wrefresh(userswin);
    usersderwin = derwin(userswin, y - 2, (x - x / 10 * 8) - 2, 1, 1);
    while (1) {
        mq_receive(users_mq, msgbuffer, 128, NULL);
        wprintw(usersderwin, "%s\n", msgbuffer);
        wrefresh(usersderwin);
    }
}