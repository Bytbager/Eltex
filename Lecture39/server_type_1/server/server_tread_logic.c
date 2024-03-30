#include "../server_type.h"

/*Поток получает дескриптор клиента через атрибут функции.
Чтобы между потоками не возникало коллизий, в войд указатель
я записываю значение дескриптора на момент создания потока,
вместо того, чтобы передавать адрес этого дескриптора.
Далее я привожу войд указатель к значению инта и пользуюсь им*/
void server_thread_logic(void *attr) {
    int client_sock = (int) attr;
    time_t result;
    char message[32];
    memset(message, 0, 32);

    /*Записываем в сообщение текущее время*/
    result = time(NULL);
    strcat(message, asctime(localtime(&result)));

    /*Отправляем сообщение клиенту, закрываем дескриптор
    и завершаем поток*/
    if (send(client_sock, message, 32, 0) == -1)
        errExit("send error!\n");

    if (close(client_sock) == -1)
        errExit("close cli_sock error!\n");
    
    pthread_exit(NULL);
}