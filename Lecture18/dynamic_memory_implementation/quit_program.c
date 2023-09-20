#include "subscriber_list.h"

int quit_program(int *subscriber_count, struct People *list, int error) {
    free(list);
    return error;
}