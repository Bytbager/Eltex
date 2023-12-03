#include "../client_sockraw.h"

/*
Функция при ошибке в программе выводит текст ошибки
и завершает программу.
*/
void errExit(char *errstr) {
    perror(errstr);
    exit(EXIT_FAILURE);
}