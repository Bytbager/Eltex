#include "byte_shift.h"
/*
Функция применяет операцию побитового сдвига влево к числу
number, на количество bits бит.

Входные данные:
    int number - число, над которым проводится операция.
    int bits - количество бит, на которое происходит сдвиг.
    int *res - указатель на переменную, в которую записывается результат.

Возвращаемые значения:
    int err - код ошибки.
*/
int left_shift(int number, int bits, int *result) {
    int error = OK;
    *result = number << bits;
    return error;
}