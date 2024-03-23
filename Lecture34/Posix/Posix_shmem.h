#ifndef __POSIX_SHMEM_H__
#define __POSIX_SHMEM_H__

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define SHMEM "/shmem"
#define SEM "/semaphore"

void errExit(char *errstr);

#endif //__POSIX_SHMEM_H__