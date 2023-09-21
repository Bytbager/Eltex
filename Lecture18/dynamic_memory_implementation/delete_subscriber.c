#include "subscriber_list.h"
/*
Функция сравнивает номера телефона, записанного в buffer
со всеми номерами в списке list, первое совпадение начинает
перестановку всех последующих абонентов на один элемент
ближе к началу списка.

Входные данные:
int *subscriber_count - указатель на текущее количество абонентов в списке,
    при успешном удалении абонента, он уменьшается на единицу.
struct People *list - указатель на начало списка абонентов.

Возвращаемые значения:
#define OK 0 - при успешном удалении абонента.
#define ERROR 1 - при отсутствии номера, по которому производится поиск
    в списке.
*/
int delete_subscriber(int *subscriber_count, struct People *list) {
    int err = OK;
    int index = 0;
    int inner_index = 0;
    int delete_flag = 0;
    char *buffer = malloc(2048);
    if (buffer == NULL) {
        perror("Buffer didn't get memory!\n");
        err = ERROR;
        quit_program(subscriber_count, list, err);
    }
    printf("Input subscriber's phone number:\n");
    scanf("%s", buffer);
    for (index; index < *subscriber_count; index++) {
        if (strcmp(list[index].phone_number, buffer) == 0) {
            for (inner_index = index; inner_index < *subscriber_count - 1; inner_index++) {
                strcpy(list[inner_index].name, list[inner_index + 1].name);
                strcpy(list[inner_index].surname, list[inner_index + 1].surname);
                strcpy(list[inner_index].phone_number, list[inner_index + 1].phone_number);
            }
            delete_flag+=1;
            *subscriber_count-=1;
            free(list[*subscriber_count].name);
            free(list[*subscriber_count].surname);
            free(list[*subscriber_count].phone_number);
            break;
        }
    }
    if (delete_flag == 0) {
        printf("Subscriber with this number not found!\n");
        err = ERROR;
    } else {
        printf("Subscriber deleted!\n");
    }
    free(buffer);
    return err;
}