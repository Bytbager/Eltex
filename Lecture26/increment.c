#include "pthread_increment.h"

extern int global_variable;
/*
Функция инкрементирует глобальную переменную на единицу
за одну итерацию цикла.

Входные данные и возвращаемые значения отсутствуют.
*/
void increment() {
    for (int i = 0; i < 1000; i++) {
        global_variable+=1;
    }
}