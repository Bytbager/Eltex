#include "pipe.h"

int pipe_child(int read_fd, int write_fd) {
    char *message = malloc(32);
    if (message == NULL) {
        perror("Child didn't get the memory!\n");
        return MALLOC_ERROR;
    }
    read(read_fd, message, 32);
    write(1, message, 16);
    write(write_fd, "Hello, Parent!\n", 16);
    free(message);
    return SUCCESS;
}