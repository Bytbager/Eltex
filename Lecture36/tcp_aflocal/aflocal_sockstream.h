#ifndef __AFLOCALSOCKSTREAM_H__
#define __AFLOCALSOCKSTREAM_H__

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SUN_PATH "/tmp/stream_serv"

void errExit(char *errstr);

#endif //__AFLOCALSOCKSTREAM_H__