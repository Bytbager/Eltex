#include "subscriber_list.h"

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