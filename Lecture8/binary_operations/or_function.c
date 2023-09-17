#include "binary_operations.h"
/*
Функция применяет битовую операцию | к числам first и second.

Входные данные:
    int first - первое число в выражении.
    int second - второе число в выражении.
    int *res - указатель на переменную, в которую записывается результат.

Возвращаемые значения:
    int err - код ошибки.
*/
int or_function(int first, int second, int *res) {
    int err = OK;
        *res = first | second;
    return err;
}