#include "../my_chat.h"

int main() {
    int y, x;
    mqd_t stocDS;
    mqd_t ctosDS;
    WINDOW *win1;
    WINDOW *win2;
    pthread_t userslist_thread;
    // stocDS = mq_open(STOC, O_RDONLY);
    // if (stocDS == -1)
    //     errExit("mq_open RDONLY stocDS\n");
    ctosDS = mq_open(CTOS, O_WRONLY);
    if (ctosDS == -1)
        errExit("mq_open WRONLY ctosDS\n");
    initscr();
    start_screen(ctosDS);
    // pthread_create(&userslist_thread, NULL, (void *) userlist, NULL);
    // pthread_join(userslist_thread, NULL);
    endwin();
    return 0;
}