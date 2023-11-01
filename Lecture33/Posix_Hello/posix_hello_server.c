#include "posix_hello.h"

int main() {
    mqd_t mq_des_stoc;
    mqd_t mq_des_ctos;
    struct mq_attr attr;    /*Создаем структуру mq_attr для изменения атрибутов очереди*/
    attr.mq_maxmsg = 10;    /*В моей системе по стандарту в очереди 10 сообщений, я оставил также*/
    attr.mq_msgsize = 128;  /*А вот размер сообщения я решил поменять, по стандарту моей системы размер*/
                            /*8 килобайт, я поставил всего 128 байт*/
    char *recv_buff;
    unsigned int recv_prio = 0;
    mq_des_stoc = mq_open(STOC, O_CREAT , 0666, &attr); /*Создаем первую очередь сообщений*/
    if (mq_des_stoc == -1)
        errExit("mq_open stoc creat error\n");
    if (mq_close(mq_des_stoc) == -1)
        errExit("mq_close stoc creat error\n");
    mq_des_stoc = mq_open(STOC, O_WRONLY);              /*Открываем ее для записи */
    if (mq_des_stoc == -1)
        errExit("mq_open stoc wronly error\n");
    mq_des_ctos = mq_open(CTOS, O_CREAT, 0666, &attr);  /*Создаем вторую очередь сообщений*/
    if (mq_des_ctos == -1)
        errExit("mq_open ctos creat error\n");
    if (mq_close(mq_des_ctos) == -1)
        errExit("mq_close ctos creat error\n");
    mq_des_ctos = mq_open(CTOS, O_RDONLY);              /*Её уже открываем для чтения*/
    if (mq_des_ctos == -1)
        errExit("mq_open ctos rdonly error\n");
    if (mq_send(mq_des_stoc, "Hello!\n", strlen("Hello!\n"), 1) == -1)  /*Отправляем сообщение в очередь Server to Client*/
        errExit("mq_send error\n");
    if (mq_getattr(mq_des_ctos, &attr) == -1)           /*Получаем текущие атрибуты очереди Client to Server*/
        errExit("mq_getattr error\n");
    recv_buff = calloc(1, attr.mq_msgsize);             /*Используем атрибут mq_msgsize для выделения памяти под буффер,*/
    if (recv_buff == NULL)                              /*в который будем получать сообщение, я сделал это, чтобы быть*/
                                                        /*уверенным в том, что памяти будет не меньше, чем значение атрибута*/
        errExit("calloc error\n");
    if (mq_receive(mq_des_ctos, (char *) recv_buff, attr.mq_msgsize, &recv_prio) == -1) /*Получаем сообщение из очереди Client to Server*/
        errExit("mq_recieve error\n");
    printf("client: %s", recv_buff);                    /*Выводим его на экран*/
    if (mq_close(mq_des_stoc) == -1)                    /*Далее закрываем и удаляем учереди, также высвобождаем память*/
        errExit("mq_close stoc error\n");
    if (mq_close(mq_des_ctos) == -1)
        errExit("mq_close ctos error\n");
    if (mq_unlink(STOC) == -1)
        errExit("mq_unlink stoc error\n");
    if (mq_unlink(CTOS) == -1)
        errExit("mq_unlink ctos error\n");
    free(recv_buff);
    return 0;
}