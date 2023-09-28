#include "shop.h"

extern pthread_key_t threads_key;
extern pthread_once_t thread_once;
/*
Функция создает поток типа "погрузчик".

Потоку присваивается область памяти для хранения его
параметров, также эти параметры сразу заполняются.

В поле thread_type структуры thread_args записывается
значение #define LOADER 1.

В поле need структуры thread_args записывается
значение 0.

Входные данные и возвращаемые значения отсутствуют.
*/
void loader_create() {
    struct thread_args *loader_args;
    pthread_once(&thread_once, create_thread_key);
    loader_args = pthread_getspecific(threads_key);
    if (loader_args == NULL) {
        loader_args = malloc(sizeof(struct thread_args));
        if (loader_args == NULL) {
            perror("Loader thread didn't get memory!\n");
            exit(EXIT_FAILURE);
        }
        pthread_setspecific(threads_key, loader_args);
    }
    loader_args->thread_type = LOADER;
    loader_args->need = 0;
    shopping(loader_args);
}