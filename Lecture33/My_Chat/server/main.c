#include "../my_chat.h"

int main() {
    mqd_t read_mqds, write_mqds, user_thread_mqds, msg_thread_mqds;
    struct mq_attr attrs = {
        .mq_maxmsg = 10,
        .mq_msgsize = 256
    };
    pthread_t user_thread, msg_thread;
    pthread_attr_t attr;
    char buff[256];
    int prio = 0;

    /*Создаем и открываем очередь для отправки подтверждений подключения
    клиентов*/
    write_mqds = mq_open(SERVTOCLI, O_CREAT, 0666, &attrs);
    if (write_mqds == -1)
        errExit("write_mqds o_creat error!\n");
    if (mq_close(write_mqds) == -1)
        errExit("write creat close error!\n");
    write_mqds = mq_open(SERVTOCLI, O_WRONLY);
    if (write_mqds == -1)
        errExit("write o_wronly open error!\n");

    /*Создаем и открываем очередь для чтения сообщений от клиентов*/
    read_mqds = mq_open(CLITOSERV, O_CREAT, 0666, &attrs);
    if (read_mqds == -1)
        errExit("read_mqds o_creat error!\n");
    if (mq_close(read_mqds) == -1)
        errExit("read creat close error!\n");
    read_mqds = mq_open(CLITOSERV, O_RDONLY);
    if (read_mqds == -1)
        errExit("read o_rdonly open error!\n");

    /*Создаем и открываем очередь для общения с потоком, отвечающим за пользователей*/
    user_thread_mqds = mq_open(SERVTOUSERTHREAD, O_CREAT, 0666, &attrs);
    if (user_thread_mqds == -1)
        errExit("user_thread_mqds o_creat error!\n");
    if (mq_close(user_thread_mqds) == -1)
        errExit("user_thread_mqds creat close error!\n");
    user_thread_mqds = mq_open(SERVTOUSERTHREAD, O_WRONLY);
    if (user_thread_mqds == -1)
        errExit("user_thread_mqds o_wronly open error!\n");

    /*Создаем и открываем очередь для общения с потоком, отвечающим за сообщения*/
    msg_thread_mqds = mq_open(SERVTOMSGTHREAD, O_CREAT, 0666, &attrs);
    if (msg_thread_mqds == -1)
        errExit("msg_thread_mqds o_creat error!\n");
    if (mq_close(msg_thread_mqds) == -1)
        errExit("msg_thread_mqds creat close error!\n");
    msg_thread_mqds = mq_open(SERVTOMSGTHREAD, O_WRONLY);
    if (msg_thread_mqds == -1)
        errExit("msg_thread_mqds o_wronly open error!\n");

    if (pthread_attr_init(&attr) != 0)
        errExit("pthread_attr_init error!\n");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        errExit("pthread_attr_setdetach_state error!\n");

    /*Запускаем потоки*/    
    pthread_create(&user_thread, &attr, (void *) users_thread, &write_mqds);
    pthread_create(&msg_thread, &attr, (void *) message_thread, NULL);

    /*В бесконечном цикле слушаем сообщения клиентов*/
    while (1) {
        if (mq_receive(read_mqds, buff, 256, &prio) == -1)
            errExit("mq_receive error!\n");

        /*Если приоритет NEW_USER или DELETED_USER
        отправляем сообщение в поток пользователей*/
        if (prio == NEW_USER || prio == DELETED_USER) {
            mq_send(user_thread_mqds, buff, 256, prio);
        }

        /*Если приоритет MESSAGE - отправляем сообщение
        в поток сообщений*/ 
        if (prio == MESSAGE) {
            if (mq_send(msg_thread_mqds, buff, 256, prio) == -1)
                errExit("mq_send to msg_thread error!\n");
        }
    }

    return 0;
}