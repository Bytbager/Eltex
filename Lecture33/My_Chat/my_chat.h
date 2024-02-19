#ifndef __MY_CHAT_H__
#define __MY_CHAT_H__

#include <fcntl.h>
#include <malloc.h>
#include <mqueue.h>
#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#define STOC "/chat_stoc"    /*Название для очереди Server to Client*/
#define CTOS "/chat_ctos"    /*Название для очереди Client to Server*/
#define USERS_MQ "/users_mq" /*Название для очереди передачи от сервара клиентам имен пользователей*/

struct User {
    pid_t pid;
    char nickname[128];
};

void errExit(char *errstr);
void sig_winch(int signo);
void userlist(void);
int start_screen(mqd_t ctosDS);

#endif //__MY_CHAT_H__