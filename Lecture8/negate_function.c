#include "binary_operations.h"

int negate_function(int *res) {
    int err = OK;
    if (*res != *res) {
        err = ERROR;
    } else {
        *res = ~ *res;
    }
    return err;
}