#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child;
    int status;

    child = fork();
    if (child == 0) {
    printf("PID: %d\nPPID: %d\n", getpid(), getppid());
    execl("/bin/ls", "ls", "-la", NULL);
    }
    else {
        wait(&status);
        printf("PID: %d\nPPID: %d\n", getpid(), getppid());
    }
    return 0;
}