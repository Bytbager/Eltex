#include "subscriber_list.h"

int new_subscriber(int *subscriber_count, struct People *list) {
    int err = OK;
    // char *buffer = NULL;
    // buffer = malloc(2048);
    // if (buffer == NULL) {
    //     perror("Buffer didn't get memory!\n");
    //     err = ERROR;
    //     quit_program(subscriber_count, list, err);
    // }
    printf("Input subscriber's name:\n");
    scanf("%s", list[*subscriber_count].name);
    // list[*subscriber_count].name = malloc(strlen(buffer) + 1);
    // if (list[*subscriber_count].name == NULL) {
    //     perror("List.name didn't get memory!\n");
    //     err = ERROR;
    //     quit_program(subscriber_count, list, err);
    // }
    // strncat(list[*subscriber_count].name, buffer, strlen(buffer) + 1);
    printf("Input subscriber's surname:\n");
    scanf("%s", list[*subscriber_count].surname);
    // list[*subscriber_count].surname = malloc(strlen(buffer) + 1);
    // if (list[*subscriber_count].surname == NULL) {
    //     perror("List.surname didn't get memory!\n");
    //     err = ERROR;
    //     quit_program(subscriber_count, list, err);
    // }
    // strncat(list[*subscriber_count].surname, buffer, strlen(buffer) + 1);
    printf("Input subscriber's phone number:\n");
    scanf("%s", list[*subscriber_count].phone_number);
    // list[*subscriber_count].phone_number = malloc(strlen(buffer) + 1);
    // if (list[0].phone_number == NULL) {
    //     perror("List.phone_number didn't get memory!\n");
    //     err = ERROR;
    //     quit_program(subscriber_count, list, err);
    // }
    // strncat(list[*subscriber_count].phone_number, buffer, strlen(buffer) + 1);
    printf("New subscriber added!\n");
    *subscriber_count+=1;
    // free(buffer);
    return err;
}