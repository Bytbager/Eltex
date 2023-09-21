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
    char *buffer = NULL;
    buffer = malloc(2048);
    if (buffer == NULL) {
        perror("Buffer didn't get memory!\n");
        err = ERROR;
        quit_program(subscriber_count, list, err);
    }
    printf("Input subscriber's name:\n");
    scanf("%s", buffer);
    list[*subscriber_count].name = strndup(buffer, strlen(buffer));
    printf("Input subscriber's surname:\n");
    scanf("%s", buffer);
    list[*subscriber_count].surname = strndup(buffer, strlen(buffer));
    printf("Input subscriber's phone number:\n");
    scanf("%s", buffer);
    list[*subscriber_count].phone_number = strndup(buffer, strlen(buffer));
    printf("New subscriber added!\n");
    *subscriber_count+=1;
    free(buffer);
    return err;
}