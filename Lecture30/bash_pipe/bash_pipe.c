#include "bash_pipe.h"

int main(int argc, char **argv) {
    int pipeFd[2];
    int index = 1;
    if (pipe(pipeFd) == -1) {
        perror("pipe error\n");
        exit(EXIT_FAILURE);
    }
    bash_pipe_ls(pipeFd);
    bash_pipe_wc(pipeFd);
    if (close(pipeFd[0]) == -1) {
        perror("close parent 1 error\n");
        exit(EXIT_FAILURE);
    }
    if (close(pipeFd[1]) == -1) {
        perror("close parent 2 error\n");
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) == -1) {
        perror("wait 1 error\n");
        exit(EXIT_FAILURE);
    }
    if (wait(NULL) == -1) {
        perror("wait 2 error\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}