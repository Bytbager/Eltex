#ifndef __MY_CHAT_SHMEM_H__
#define __MY_CHAT_SHMEM_H__

#include <fcntl.h>
#include <malloc.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SEMAPHORE_USERS "users"
#define SHMEM_USER "user_shmem"
#define SEMAPHORE_MSG "message"
#define SHMEM_MSG "msg_shmem"
#define PROJ_ID 1

struct user {
    pid_t pid;
    char nickname[32];
};

struct args {
    WINDOW *main_win;
    WINDOW *print_win;
    void *user;
};

void errExit(char *errstr);
void users_thread(void);
void message_thread(void);
void sig_winch(int signo);
void start_screen(struct user *me);
void user_list_thread(void);
void message_create_thread(void);
void cleanup_thread(void *args);
void message_history_thread(void);

#endif //__MY_CHAT_SHMEM_H__