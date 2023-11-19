#ifndef __AFINETSOCKSTREAM_H__
#define __AFINETSOCKSTREAM_H__

#include <malloc.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 7777

void errExit(char *errstr);

#endif //__AFINETSOCKSTREAM_H__