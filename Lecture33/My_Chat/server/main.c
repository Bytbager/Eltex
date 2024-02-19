#include "../my_chat.h"

pthread_cond_t userlist_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t servmutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    mqd_t stocDS;
    mqd_t ctosDS;
    mqd_t users_mqDS;
    char *recv_buff;
    unsigned int prio;
    struct mq_attr attr;
    pthread_t listen_thread;
    pthread_t write_thread;
    int status = 0;
    struct User *bim = malloc(sizeof(struct User *));
    ctosDS = mq_open(CTOS, O_CREAT, 0666, NULL);
    if (ctosDS == -1)
        errExit("mq_open O_CREAT ctosDS\n");
    if (mq_close(ctosDS) == -1)
        errExit("mq_close ctosDS O_CREAT\n");
    ctosDS = mq_open(CTOS, O_RDONLY);
    if (ctosDS == -1)
        errExit("mq_open RDONLY ctosDS\n");
    // char **users = malloc(sizeof(char *) * 10);
    // for (int i = 0; i < 10; i++)
    //     users[i] = malloc(attr.mq_msgsize);
    // stocDS = mq_open(STOC, O_CREAT, 0666, &attr);
    // if (stocDS == -1)
    //     errExit("mq_open O_CREAT stocDS\n");
    // users_mqDS = mq_open(USERS_MQ, O_CREAT, 0666, &attr);
    // if (users_mqDS == -1)
    //     errExit("mq_open O_CREAT users_mqDS\n");
    // if (mq_close(stocDS) == -1)
    //     errExit("mq_close stocDS O_CREAT\n");
    // if (mq_close(users_mqDS) == -1)
    //     errExit("mq_close users_mqDS O_CREAT\n");
    // stocDS = mq_open(STOC, O_WRONLY);
    // if (stocDS == -1)
    //     errExit("mq_open WRONLY stocDS\n");
    // users_mqDS = mq_open(USERS_MQ, O_WRONLY);
    // if (users_mqDS == -1)
    //     errExit("mq_open users_mq wronly error\n");
    mq_getattr(ctosDS, &attr);
    char *msgbuffer = malloc(attr.mq_msgsize);
    while (1) {
        status = mq_receive(ctosDS, msgbuffer, attr.mq_msgsize, &prio);
        printf("read: %d, prio: %u\n", status, prio);
        if (prio == 32) {
            bim = (struct User *)msgbuffer;
            printf("%d\n", bim->pid);
            printf("%s\n", bim->nickname);
        }
        // mq_send(users_mqDS, msgbuffer, 128, 0);
    }
    // for (int i = 0; i < 10; i++)
    //     free(users[i]);
    // free(users);
    return 0;
}