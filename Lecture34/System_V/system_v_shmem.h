#ifndef __SYSTEM_V_SHMEM_H__
#define __SYSTEM_V_SHMEM_H__

#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SEMAPHORE "semaphore"
#define SHMEM_SEGMENT "shm_segment"
#define PROJ_ID 1

void errExit(char *errstr);

#endif //__SYSTEM_V_SHMEM_H__