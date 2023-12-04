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
#define CLIENT_IP "127.0.0.2"
#define SERV_PORT_NUM 7777
#define CLIENT_PORT_NUM 7778

struct udp_header {
    short source_port;
    short destination_port;
    short length;
    short checksum;
    char payload[16];
};

struct ip_header {
    uint8_t ip_ver_IHL;
    uint8_t diffservice;
    short length;
    short identification;
    short flags_offset;
    uint8_t TTL;
    uint8_t transport_proto;
    short checksum;
    uint32_t source_ip;
    uint32_t dest_ip;
};

struct message {
    struct ip_header ip;
    struct udp_header udp;
};

void errExit(char *errstr);
void message_create(struct message *msg);

#endif //__CLIENT_SOCKRAW_H__