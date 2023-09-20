#include "subscriber_list.h"
/*
Функция высвобождает память, выделенную под список list.

Входные данные:
struct People *list - указатель на начало списка абонентов.
int error - код ошибки предыдущей функции.

Возвращаемые значения:
#define OK 0 - предыдущая функция завершилась успешно.
#define ERROR 1 - предыдущая функция завершилась с ошибкой.
*/
int quit_program(struct People *list, int error) {
    free(list);
    return error;
}