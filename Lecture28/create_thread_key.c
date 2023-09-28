#include "shop.h"

extern pthread_key_t threads_key;
/*
Функция создает ключ, который виден всем потокам.
Используется для разделения областей памяти между потоками.

Входные данные и возвращаемые значения отсутствуют.
*/
void create_thread_key() {
    pthread_key_create(&threads_key, free_thread_key);
}