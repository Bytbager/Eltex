#include "../my_chat.h"

int delete_client_mq(struct user_list **root, struct User **exited_user) {
    struct user_list *tmp = *root;
    char mqname[17] = "/\0";

    while (tmp->user.pid != (*exited_user)->pid)
        tmp = tmp->next;

    if (mq_close(tmp->user.mqds) == -1)
        errExit("delete_client_mq mq_close error!\n");
    strncat(mqname, tmp->user.nickname, 16);
    if (mq_unlink(mqname) == -1)
        errExit("delete_client_mq mq_unlink error!\n");
    
    printf("mq %s deleted!\n", mqname);
    
    return 0;
}