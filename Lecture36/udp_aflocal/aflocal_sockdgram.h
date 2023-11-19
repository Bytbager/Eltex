#ifndef __AFLOCALSOCKDGRAM_H__
#define __AFLOCALSOCKDGRAM_H__

#include <arpa/inet.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SUN_PATH "/tmp/dgram_server"
#define CLIENT_SUN_PATH "/tmp/dgram_client"

void errExit(char *errstr);

#endif //__AFLOCALSOCKDGRAM_H__