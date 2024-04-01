#include "../my_chat.h"

/*Функция создаёт очередь сообщений для нового клиента*/
int create_mq_for_client(struct user_list **root, struct User **new_user) {
    struct user_list *tmp = *root;
    struct mq_attr attr = {
        .mq_maxmsg = 10,
        .mq_msgsize = 256
    };

    char mqname[17] = "/\0";

    while(tmp->user.pid != (*new_user)->pid) {
        tmp = tmp->next;
    }

    strncat(mqname, tmp->user.nickname, 16);
    if (mq_unlink(mqname) == -1 && errno != ENOENT)
        errExit("mq_unlink error!\n");
    tmp->user.mqds = mq_open(mqname, O_CREAT, 0666, &attr);
    if (tmp->user.mqds == -1)
        errExit("add_user mq_open o_creat error!\n");
    if (mq_close(tmp->user.mqds) == -1)
        errExit("add_user mq_close error!\n");
    tmp->user.mqds = mq_open(mqname, O_WRONLY);
    if (tmp->user.mqds == -1)
        errExit("add_user mq_open o_wronly error!\n");
    (*new_user)->mqds = tmp->user.mqds;
    
    return 0;
}