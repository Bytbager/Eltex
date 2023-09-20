#include "subscriber_list.h"

int new_subscriber(int *subscriber_count, struct People *list) {
    int err = OK;
    printf("Input subscriber's name:\n");
    scanf("%s", list[*subscriber_count].name);
    printf("Input subscriber's surname:\n");
    scanf("%s", list[*subscriber_count].surname);
    printf("Input subscriber's phone number:\n");
    scanf("%s", list[*subscriber_count].phone_number);
    printf("New subscriber added!\n");
    *subscriber_count+=1;
    return err;
}