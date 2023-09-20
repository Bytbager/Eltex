#include "subscriber_list.h"
/*
Функция добавляет в список нового абонента.

Входные данные:
int *subscriber_count - указатель на текущее количество абонентов в списке,
    при успешном добавлении абонента, он увеличивается на единицу.
struct People *list - указатель на начало списка абонентов.

Возвращаемые значения:
#define OK 0 - при успешном добавлении абонента.
*/
int new_subscriber(int *subscriber_count, struct People *list) {
    int err = OK;
    do {
        printf("Input subscriber's name:\n"
                "Maximum 19 symbols!\n");
        scanf("%s", list[*subscriber_count].name);
    } while (strlen(list[*subscriber_count].name) > 19);
    do {
        printf("Input subscriber's surname:\n"
                "Maximum 19 symbols!\n");
        scanf("%s", list[*subscriber_count].surname);
    } while (strlen(list[*subscriber_count].surname) > 19);
    do {
        printf("Input subscriber's phone number:\n"
                "Maximum 19 symbols!\n");
        scanf("%s", list[*subscriber_count].phone_number);
    } while (strlen(list[*subscriber_count].phone_number) > 19);
    printf("New subscriber added!\n");
    *subscriber_count+=1;
    return err;
}