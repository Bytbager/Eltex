#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child;
    int status;

    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    child = fork();
    if (child == 0) {
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
        child = fork();
        if (child == 0) {
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
        else {
            wait(&status);
            child = fork();
            if (child == 0) {
                printf("PID: %d, PPID: %d\n", getpid(), getppid());
                exit(EXIT_SUCCESS);
            }
            else {
                wait(&status);
                exit(EXIT_SUCCESS);
            }
        }
    }
    else {
        wait(&status);
        child = fork();
        if (child == 0) {
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
            child = fork();
            if (child == 0) {
                printf("PID: %d, PPID: %d\n", getpid(), getppid());
                exit(EXIT_SUCCESS);
            }
            else {
                wait(&status);
                exit(EXIT_SUCCESS);
            }
        }
        else {
            wait(&status);
        }
    }
    return 0;
}