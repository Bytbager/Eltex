#include "bash_pipe.h"

/*
Функция позволяет родителю создать потомка,
который выполняет команду ls -a, сам родитель
после создания возвращается в главную фукнкцию.

Входные данные:
    int *pipeFd - указатель на дескрипторы канала
    pipe.

Возвращаемые значения отсутствуют.
*/
void bash_pipe_ls(int *pipeFd) {
    switch(fork()) {
    case -1:
        perror("fork 1 error\n");
        exit(EXIT_FAILURE);
    case 0:
        if (close(pipeFd[0]) == -1) {
            perror("close 1 error\n");
            exit(EXIT_FAILURE);
        }
        if (pipeFd[1] != STDOUT_FILENO) {
            if (dup2(pipeFd[1], STDOUT_FILENO) == -1) {
                perror("dup2 stdout error\n");
                exit(EXIT_FAILURE);
            }
            if (close(pipeFd[1]) == -1) {
                perror("close 2 error\n");
                exit(EXIT_FAILURE);
            }
        }
        execl("/bin/ls", "ls", "-a", NULL);
        perror("execl ls -a error\n");
        exit(EXIT_FAILURE);
    default:
        break;
    }
}