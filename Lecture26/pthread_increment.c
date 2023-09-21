#include "pthread_increment.h"

int global_variable = 0;
/*
Функция создает 10000 потоков, которые выполняют функцию
инкрементации глобальной переменной.
*/
int main() {
    int index = 0;
    pthread_t thread[10000];
    int status = 0;
    for(index; index < 10000; index++) {
        pthread_create(&thread[index], NULL, (void *) increment, NULL);
    }
    index = 0;
    for(int i = 0; i < 10000; i++) {
        pthread_join(thread[i], (void **) &status);
    }
    printf("%d\n", global_variable);
    return 0;
}