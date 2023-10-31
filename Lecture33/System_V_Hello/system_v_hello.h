#ifndef __SYSTEM_V_HELLO_H__
#define __SYSTEM_V_HELLO_H__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define QUEUE_PATHNAME_STOC "queue_stoc"    /*Название для файла очереди server to client*/
#define QUEUE_PATHNAME_CTOS "queue_ctos"    /*Название для файла очереди client to server*/
#define PROJ_ID 1

void errExit(char *errstr);

#endif //__SYSTEM_V_HELLO_H__