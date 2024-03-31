#include "../server_type.h"

extern mqd_t mqds;

/*Поток получает дескриптор клиента через POSIX очередь
и отпраляет ответ клиенту*/
void server_thread_logic(void *attr) {
    time_t result;
    char message[32];
    int clientFD[4];

    /*Входим в бесконечный цикл, в котором получаем
    дескриптор клиента и отправляем ему ответ*/
    while (1) {
        memset(clientFD, 0, 128);
        if (mq_receive(mqds, (char *) clientFD, 128, NULL) == -1)
            errExit("mq_receive error!\n");
        else {
            memset(message, 0, 32);
            /*Записываем в сообщение текущее время*/
            result = time(NULL);
            strcat(message, asctime(localtime(&result)));

            /*Отправляем сообщение клиенту, закрываем дескриптор
            и завершаем поток*/
            if (send(clientFD[0], message, 32, 0) == -1)
                errExit("send error!\n");

            if (close(clientFD[0]) == -1)
                errExit("close cli_sock error!\n");
        }
    }
}