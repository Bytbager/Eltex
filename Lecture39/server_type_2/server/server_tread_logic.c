#include "../server_type.h"

extern struct thread_attr threads[10];

/*Поток получает дескриптор клиента через глобальный массив.
Чтобы между потоками не возникало коллизий, в войд указатель
я записываю номер потока на момент его создания.
Далее я привожу войд указатель к значению инта и пользуюсь им*/
void server_thread_logic(void *attr) {
    int thread_number = (int) attr;
    time_t result;
    char message[32];

    /*Входим в бесконечный цикл, в котором проверяем значение
    готовности потока, если главный поток передал нам дескриптор
    клиента, он также поменяет его статус на "THREAD_BUSY"*/
    while (1) {
        if (threads[thread_number].thread_readiness == THREAD_BUSY) {
            memset(message, 0, 32);
            /*Записываем в сообщение текущее время*/
            result = time(NULL);
            strcat(message, asctime(localtime(&result)));

            /*Отправляем сообщение клиенту, закрываем дескриптор
            и завершаем поток*/
            if (send(threads[thread_number].client_ds, message, 32, 0) == -1)
                errExit("send error!\n");

            if (close(threads[thread_number].client_ds) == -1)
                errExit("close cli_sock error!\n");
            threads[thread_number].thread_readiness = THREAD_READY;
        }
    }
}