#ifndef __BASH_PIPE_H__
#define __BASH_PIPE_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void bash_pipe_ls(int *pipeFd);
void bash_pipe_wc(int *pipeFd);

#endif //__BASH_PIPE_H__