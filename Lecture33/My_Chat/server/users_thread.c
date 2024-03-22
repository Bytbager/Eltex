#include "../my_chat.h"

struct user_list *root;
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

void users_thread(mqd_t *write_mqds) {
    mqd_t mqds;
    char message[256];
    int prio = 0;
    struct user_list *tmp;
    struct User *new_user;


    root = calloc(1, sizeof(struct user_list));
    if (root == NULL)
        errExit("root calloc error\n");
    root->user.pid = 0;

    mqds = mq_open(SERVTOUSERTHREAD, O_RDONLY);
    if (mqds == -1)
        errExit("mqds o_wronly open error!\n");

    while(1) {
        mq_receive(mqds, message, 256, &prio);
        new_user = (struct User *) message;
        
        if (prio == NEW_USER) {
            pthread_rwlock_wrlock(&lock);
            add_user(&root, &new_user);
            create_mq_for_client(&root, &new_user);
            pthread_rwlock_unlock(&lock);
            if (mq_send(*write_mqds, message, 256, NEW_USER) == -1)
                printf("wr eror!\n");
            tmp = root;
            while (tmp != NULL) {
                if (mq_send(new_user->mqds, (char *) &tmp->user, 256, NEW_USER) == -1)
                    errExit("mq_send new_user mqds error!\n");
                tmp = tmp->next;
            }
            tmp = root;
            while (tmp != NULL) {
                if (tmp->user.mqds != new_user->mqds)
                    if (mq_send(tmp->user.mqds, (char *) new_user, 256, NEW_USER) == -1)
                        errExit("mq_send tmp->user.mqds error!\n");
                tmp = tmp->next;
            }
        } else if (prio == DELETED_USER) {
            tmp = root;
            while (tmp != NULL) {
                if (tmp->user.pid == new_user->pid) {
                    mq_send(tmp->user.mqds, (char *) new_user, 256, SERVER_RECEIVED_DELETION_REQUEST);
                } else {
                    mq_send(tmp->user.mqds, (char *) new_user, 256, DELETED_USER);
                }
                tmp = tmp->next;
            }
            pthread_rwlock_wrlock(&lock);
            delete_client_mq(&root, &new_user);
            delete_user(&root, &new_user);
            pthread_rwlock_unlock(&lock);
        }
    }
}