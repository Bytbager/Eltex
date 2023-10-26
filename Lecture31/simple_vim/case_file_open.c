#include "simple_vim.h"

int case_file_open(int fildes, char *filename) {
    char *readbuffer;
    int read_value = 0;
    fildes = open(filename, O_CREAT, 00666);    /*Создаем файл, если он не создан функция не вызывает ошибку,*/
    close(fildes);                              /*но не имеет эффекта.*/

    fildes = open(filename, O_RDONLY);          /*Далее открываем файл на чтение и выводим данные на экран*/
    while (1) {
        readbuffer = calloc(1, 128);
        read_value = read(fildes, readbuffer, 128);
        printw("%s", readbuffer);
        refresh();
        free(readbuffer);
        if (read_value < 128) {
            read_value = 0;
            break;
        }
    }
    close(fildes);
    fildes = open(filename, O_WRONLY);          /*Открываем файл на запись и возвращаем открытый дескриптор из функции*/
    return fildes;
}