#include "binary_operations.h"

int and_function(int first, int second, int *res) {
    int err = OK;
    if (first != first || second != second) {
        err = ERROR;
    } else {
        *res = first & second;
    }
    return err;
}