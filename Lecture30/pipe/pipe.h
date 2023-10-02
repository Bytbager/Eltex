#ifndef __PIPE_H__
#define __PIPE_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define MALLOC_ERROR -1

int pipe_child(int read_fd, int write_fd);
int pipe_parent(int read_fd, int write_fd);

#endif //__PIPE_H__