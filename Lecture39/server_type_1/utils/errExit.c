#include "../server_type.h"
#include <errno.h>

/*
Функция при ошибке в программе выводит текст ошибки
и завершает программу.
*/
void errExit(char *errstr) {
    perror(errstr);
    exit(errno);
}