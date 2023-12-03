#ifndef __CLIENT_SOCKRAW_H__
#define __CLIENT_SOCKRAW_H__

#include <arpa/inet.h>
#include <malloc.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT_NUM 7777
#define CLIENT_PORT_NUM 7778

struct message {
    short source_port;
    short destination_port;
    short length;
    short checksum;
    char payload[16];
};

void errExit(char *errstr);

#endif //__CLIENT_SOCKRAW_H__