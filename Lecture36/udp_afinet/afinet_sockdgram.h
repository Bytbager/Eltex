#ifndef __AFINETSOCKDGRAM_H__
#define __AFINETSOCKDGRAM_H__

#include <arpa/inet.h>
#include <malloc.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT_NUM 6777

void errExit(char *errstr);

#endif //__AFINETSOCKDGRAM_H__