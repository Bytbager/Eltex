#include "pipe.h"

/*
Функция создает 2 канала для общения с потомком,
родитель использует первый канал для чтения, второй канал
для записи, потом использует каналы наоборот.

Родитель и потомок обмениваются сообщениями между собой,
после этого функция завершается.
*/
int main() {
    int first_pipe[2];
    int second_pipe[2];
    pid_t child;
    int status;
    pipe(first_pipe);
    pipe(second_pipe);
    child = fork();
    if (child == 0) {
        close(first_pipe[0]);
        close(second_pipe[1]);
        pipe_child(second_pipe[0], first_pipe[1]);
        exit(EXIT_SUCCESS);
    } else {
        close(first_pipe[1]);
        close(second_pipe[0]);
        pipe_parent(first_pipe[0], second_pipe[1]);
        wait(&status);
    }
    close(first_pipe[0]);
    close(first_pipe[1]);
    close(second_pipe[0]);
    close(second_pipe[1]);
    return 0;
}