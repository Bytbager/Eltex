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
int quit_program(int *subscriber_count, struct People *list, int error) {
    int index = 0;
    for (index; index < *subscriber_count; index++) {
        free(list[index].name);
        free(list[index].surname);
        free(list[index].phone_number);
    }
    free(list);
    return error;
}