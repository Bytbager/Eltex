#include "posix_hello.h"

int main() {
    mqd_t mq_des_stoc;
    mqd_t mq_des_ctos;
    struct mq_attr attr;
    char *recv_buff;
    unsigned int recv_prio = 0;
    mq_des_stoc = mq_open(STOC, O_RDONLY);  /*Открываем очередь Server to Client для чтения*/
    if (mq_des_stoc == -1)
        errExit("mq_open stoc error\n");
    mq_des_ctos = mq_open(CTOS, O_WRONLY);  /*Открываем очередь Client to Server для записи*/
    if (mq_des_ctos == -1)
        errExit("mq_open ctos error\n");
    if (mq_getattr(mq_des_stoc, &attr) == -1)   /*Получаем атрибуты очереди Server to Client*/
        errExit("mq_getattr error\n");
    recv_buff = calloc(1, attr.mq_msgsize); /*Выделяем память размером mq_msgsize под буффер записи*/
    if (recv_buff == NULL)
        errExit("calloc error\n");
    if (mq_receive(mq_des_stoc, (char *) recv_buff, attr.mq_msgsize, &recv_prio) == -1) /*Получаем сообщение от сервера*/
        errExit("mq_recieve error\n");
    printf("server: %s", recv_buff);    /*Выводим его на экран*/
    if (mq_send(mq_des_ctos, "Hi!\n", strlen("Hi!\n"), 1) == -1)    /*Отправляем серверу ответ*/
        errExit("mq_send error\n");
    if (mq_close(mq_des_stoc) == -1)        /*Закрываем очереди и высвобождаем память*/
        errExit("mq_close stoc error\n");
    if (mq_close(mq_des_ctos) == -1)
        errExit("mq_close ctos error\n");
    free(recv_buff);
    return 0;
}