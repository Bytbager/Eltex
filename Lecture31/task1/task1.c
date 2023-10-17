#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int fildes;
    char message[8];
    /*Создаем файл с помощью флага O_CREAT*/
    if ((fildes = open("filename.txt", O_CREAT, S_IRWXU)) == -1) {
        perror("open creat error\n");
        _exit(-1);
    }
    /*Закрываем дескриптор*/
    if (close(fildes) == -1) {
        perror("close creat error\n");
        _exit(-1);
    }
    /*Окрываем файл, но уже для записи*/
    if ((fildes = open("filename.txt", O_WRONLY)) == -1) {
        perror("open wronly error\n");
        _exit(-1);
    }
    /*Записываем строку в файл*/
    if (write(fildes, "Hello!\n", 8) == -1) {
        perror("write error\n");
        _exit(-1);
    }
    /*Снова закрываем дескриптор*/
    if (close(fildes) == -1) {
        perror("close wronly error\n");
        _exit(-1);
    }
    /*Открываем файл для чтения*/
    if ((fildes = open("filename.txt", O_RDONLY)) == -1) {
        perror("open rdonly error\n");
        _exit(-1);
    }
    /*Читаем строку из файла*/
    if (read(fildes, message, 8) == -1) {
        perror("read error\n");
        _exit(-1);
    }
    /*Закрываем дескриптор*/
    if (close(fildes) == -1) {
        perror("close rdonly error\n");
        _exit(-1);
    }
    /*Удаляем файл*/
    if (remove("./filename.txt") == -1) {
        perror("remove error\n");
        _exit(-1);
    }
    /*Пишем строку, считанную из файла в стандартный поток вывода*/
    if (write(1, message, 8) == -1) {
        perror("write fd 1 error\n");
        _exit(-1);
    }
    return 0;
}