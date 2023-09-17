#include "hexadecimal_number.h"
/*
Функция меняет третий байт числа number на значение,
указанное в переменной byte.

Входные данные:
    int number - число, над которым проводится операция.
    int byte - новое значение изменяемого байта.
    int *res - указатель на переменную, в которую записывается результат.

Возвращаемые значения:
    int err - код ошибки.
*/
int third_byte_change(int number, int byte, int *result) {
    int err = OK;
    number = number & THIRD_BYTE;
    *result = number | (byte << 16);
    return err;
}