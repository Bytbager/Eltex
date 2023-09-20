#include "subscriber_list.h"

int show_subscriber_list(int *subscriber_count, struct People *list) {
    int err = OK;
    int index = 0;
    if (*subscriber_count == 0) {
        printf("There are no subscribers in the list!\n"
                "Try to add subscribers before!\n\n");
        return err;
    } else {
        for (index; index < *subscriber_count; index++) {
            printf("%s %s %s\n", list[index].name, list[index].surname, list[index].phone_number);
        }
        return err;
    }
}