#ifndef __SERVER_TYPE__
#define __SERVER_TYPE__

#include <arpa/inet.h>
#include <fcntl.h>
#include <malloc.h>
#include <mqueue.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SERVER_IP "127.1.1.1"
#define SERVER_PORT 7777
#define THREAD_READY 0
#define THREAD_BUSY 1

struct thread_attr {
    int thread_readiness;
    int client_ds;
};

void errExit(char *errstr);
void server_thread_logic(void *attr);
void client_thread_logic(void *attr);

#endif //__SERVER_TYPE__