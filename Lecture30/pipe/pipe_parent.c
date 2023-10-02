#include "pipe.h"

int pipe_parent(int read_fd, int write_fd) {
    char *message = malloc(32);
    if (message == NULL) {
        perror("Parent didn't get the memory!\n");
        return MALLOC_ERROR;
    }
    write(write_fd, "Hello, Child!\n", 15);
    read(read_fd, message, 32);
    write(1, message, 16);
    free(message);
    return SUCCESS;
}