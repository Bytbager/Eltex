#include "../my_chat.h"

extern struct user_list *root;
extern pthread_rwlock_t lock;

void message_thread() {
    mqd_t mqds;
    char *buffer, *message_history;
    int prio = 0;
    struct user_list *tmp;

    buffer = calloc(256, sizeof(char));
    if (buffer == NULL)
        errExit("buffer msg_thread calloc error!\n");
    
    message_history = calloc(1, 1);
    if (message_history == NULL)
        errExit("message_history calloc error!\n");

    /*Открываем очередь для общения с главным потоком*/
    mqds = mq_open(SERVTOMSGTHREAD, O_RDONLY);
    if (mqds == -1)
        errExit("mq_open msg_thread error!\n");

    /*Принимаем сообщения в бесконечном цикле*/
    while (1) {
        memset(buffer, 0, 256);
        if (mq_receive(mqds, buffer, 256, &prio) == -1)
            errExit("mq_receive msg_thread error!\n");

        /*Отправляем полученные сообщения всем клиентам из списка*/
        pthread_rwlock_rdlock(&lock);
        tmp = root;
        while (tmp != NULL) {
            if (mq_send(tmp->user.mqds, buffer, 256, MESSAGE) == -1)
                errExit("mq_send tmp->user.mqds error!\n");
            tmp = tmp->next;
        }
        pthread_rwlock_unlock(&lock);
    }
}