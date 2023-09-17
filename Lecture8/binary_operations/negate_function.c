#include "binary_operations.h"
/*
Функция применяет битовую операцию ~ к числу number.

Входные данные:
    int number - число, над которым проводится операция.
    int *res - указатель на переменную, в которую записывается результат.

Возвращаемые значения:
    int err - код ошибки.
*/
int negate_function(int number, int *res) {
    int err = OK;
        *res = ~ number;
    return err;
}