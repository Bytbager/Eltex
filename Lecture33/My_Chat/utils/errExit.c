#include "../my_chat.h"

/*
Функция при ошибке в программе выводит текст ошибки
и завершает программу.
*/
void errExit(char *errstr) {
    endwin();
    perror(errstr);
    exit(EXIT_FAILURE);
}