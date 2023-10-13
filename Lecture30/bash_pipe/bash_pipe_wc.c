#include "bash_pipe.h"

/*
Функция позволяет родителю создать потомка,
который выполняет команду wc -l, сам родитель
после создания возвращается в главную фукнкцию.

Входные данные:
    int *pipeFd - указатель на дескрипторы канала
    pipe.

Возвращаемые значения отсутствуют.
*/
void bash_pipe_wc(int *pipeFd) {
    switch(fork()) {
    case -1:
        perror("fork 2 error\n");
        exit(EXIT_FAILURE);
    case 0:
        if (close(pipeFd[1]) == -1) {
            perror("close 3 error\n");
            exit(EXIT_FAILURE);
        }
        if (pipeFd[0] != STDIN_FILENO) {
            if (dup2(pipeFd[0], STDIN_FILENO) == -1) {
                perror("dup2 stdin error\n");
                exit(EXIT_FAILURE);
            }
            if (close(pipeFd[0]) == -1) {
                perror("close 4 error\n");
                exit(EXIT_FAILURE);
            }
        }
        execl("/bin/wc", "wc", "-l", NULL);
        perror("execl wc -l error\n");
        exit(EXIT_FAILURE);
    default:
        break;
    }
}