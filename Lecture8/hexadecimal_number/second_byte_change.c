#include "hexadecimal_number.h"
/*
Функция меняет второй байт числа number на значение,
указанное в переменной byte.

Входные данные:
    int number - число, над которым проводится операция.
    int byte - новое значение изменяемого байта.
    int *res - указатель на переменную, в которую записывается результат.

Возвращаемые значения:
    int err - код ошибки.
*/
int second_byte_change(int number, int byte, int *result) {
    int err = OK;
    number = number & SECOND_BYTE;
    *result = number | (byte << 8);
    return err;
}