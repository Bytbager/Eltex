#include "subscriber_list.h"
/*
Функция добавляет в список нового абонента.

Входные данные:
int *subscriber_count - указатель на текущее количество абонентов в списке.
struct People *list - указатель на начало списка абонентов.

Возвращаемые значения:
#define OK 0 - при присутствии в списке хотя бы одного абонента.
#define ERROR 1 - при отсутствии абонентов в списке.
*/
int show_subscriber_list(int *subscriber_count, struct People *list) {
    int err = OK;
    int index = 0;
    if (*subscriber_count == 0) {
        printf("There are no subscribers in the list!\n"
                "Try to add subscribers before!\n\n");
        err = ERROR;
        return err;
    } else {
        for (index; index < *subscriber_count; index++) {
            printf("%s %s %s\n", list[index].name, list[index].surname, list[index].phone_number);
        }
        return err;
    }
}