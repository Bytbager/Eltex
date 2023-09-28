#include "shop.h"

extern pthread_key_t threads_key;
extern pthread_once_t thread_once;
/*
Функция создает поток типа "покупатель".

Потоку присваивается область памяти для хранения его
параметров, также эти параметры сразу заполняются.

В поле thread_type структуры thread_args записывается
значение #define CUSTOMER 2.

В поле need структуры thread_args записывается
значение 10000.

Входные данные и возвращаемые значения отсутствуют.
*/
void customer_create() {
    struct thread_args *customer_args;
    pthread_once(&thread_once, create_thread_key);
    customer_args = pthread_getspecific(threads_key);
    if (customer_args == NULL) {
        customer_args = malloc(sizeof(struct thread_args));
        if (customer_args == NULL) {
            perror("Customer thread didn't get memory!\n");
            exit(EXIT_FAILURE);
        }
        pthread_setspecific(threads_key, customer_args);
    }
    customer_args->thread_type = CUSTOMER;
    customer_args->need = 10000;
    shopping(customer_args);
}