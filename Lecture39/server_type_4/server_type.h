#ifndef __SERVER_TYPE__
#define __SERVER_TYPE__

#include <arpa/inet.h>
#include <malloc.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SERVER_IP "127.1.1.1"
#define TCP_PORT 7777
#define UDP_PORT 8888

void errExit(char *errstr);

#endif //__SERVER_TYPE__