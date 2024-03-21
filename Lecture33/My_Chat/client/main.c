#include "../my_chat.h"

int main() {
    mqd_t read_mqds, write_mqds;
    struct User me;
    memset(&me, 0, sizeof(struct User));
    char mqname[17] = "/\0";
    int prio = 0;
    char buff[256];

    pthread_t msg_hist_thread, msg_create_thread, user_thread;
    pthread_attr_t attr;
    // struct msg_create_args args;
    int msg_history_pipe[2], msg_create_pipe[2], user_list_pipe[2]; 

    if (pthread_attr_init(&attr) != 0)
        errExit("pthread_attr_init error!\n");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        errExit("pthread_attr_setdetach_state error!\n");

    read_mqds = mq_open(SERVTOCLI, O_RDONLY);       /*Открываем очередь для чтения*/
    if (read_mqds == -1)
        errExit("read open error!\n");
    write_mqds = mq_open(CLITOSERV, O_WRONLY);      /*Открываем очередь для записи*/
    if (write_mqds == -1)
        errExit("write open error!\n");

    initscr();
    signal(SIGWINCH, sig_winch);
    // start_color();
    cbreak();
    curs_set(FALSE);
    // init_pair(1, COLOR_WHITE, COLOR_BLUE);
    // attron(COLOR_PAIR(1));
    // bkgd(COLOR_PAIR(1));
    refresh();
    start_screen(&me);


    // if (pipe(msg_create_pipe) == -1)
    //     errExit("msg_create_pipe error!\n");
    // args.read_pipe = &msg_create_pipe[0];
    // args.write_mqds = &write_mqds;
    if (pthread_create(&msg_create_thread, &attr, (void *) message_create_thread, &write_mqds) != 0)
        errExit("pthread_create message_create_thread error!\n");

    if (pipe(msg_history_pipe) == -1)
        errExit("msg_history_pipe error!\n");
    if (pthread_create(&msg_hist_thread, &attr, (void *) message_history_thread, &msg_history_pipe[0]) != 0)
        errExit("pthread_create message_history_thread error!\n");
    if (pipe(user_list_pipe) == -1)
        errExit("user_list_pipe error!\n");
    if (pthread_create(&user_thread, &attr, (void *) user_list_thread, &user_list_pipe[0]) != 0)
        errExit("pthread_create user_thread error!\n");

    if (mq_send(write_mqds, (char *) &me, 256, 32) != 0) {
        errExit("mq_send error!\n");
    }
    mq_receive(read_mqds, buff, 256, &prio);
    if (prio == 32) {
        strncat(mqname, me.nickname, 16);
        me.mqds = mq_open(mqname, O_RDONLY);
        if (me.mqds == -1)
            errExit("me mq_open o_rdonly error!\n");
        prio = 0;
    }
    // char hello[256];
    // memset(hello, 0, 256);
    // strncat(hello, "hello!\0", 7);
    // if (mq_send(write_mqds, hello, 256, 1) == -1)
    //     errExit("mq_send hello error!\n");
    while (1) {
        memset(buff, 0, 256);
        if (mq_receive(me.mqds, buff, 256, &prio) == -1)
            errExit("receive me.mqds error!\n");
        if (prio == 32) {
            if (write(user_list_pipe[1], (struct User *) buff, sizeof(struct User)) == -1)
                errExit("write user_list_pipe error!\n");
        }
        else if (prio == 1) {
            if (write(msg_history_pipe[1], buff, strlen(buff)) == -1)
                errExit("write msg_history_pipe error!\n");
        }
    }
    // char pref[22 + 256];
    // while (1) {
    //     memset(pref, 0, 22 + 256);
    //     strncat(pref, me.nickname, 17);
    //     strncat(pref, ": ", 3);
    //     memset(buff, 0, 256);
    //     scanf("%s", buff);
    //     strncat(pref, buff, 256);
    //     strncat(pref, "\n", 2);
    //     if (mq_send(write_mqds, pref, 256 + 22, 1) == -1) {
    //         errExit("mq_send error cli!\n");
    //     }
    // }

    endwin();    
    // mq_send(write_mqds, (char *) &me, 256, 33);
    return 0;
}