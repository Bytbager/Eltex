#include "../my_chat_shmem.h"

/*Функция очистки потока, она выполняется
после вызова pthread_cancel.

void *args - указатель на аргументы для очистки
его нужно привести к виду (struct args *) для работы*/
void cleanup_thread(void *args) {
    struct args *tmp = (struct args *) args;
    if (tmp->main_win != NULL)
        delwin(tmp->main_win);
    if (tmp->print_win != NULL)
        delwin(tmp->print_win);
    if (tmp->user != NULL)
        if (shmdt(tmp->user) == -1)
            errExit("shmdt clean user_thread error!\n");
}