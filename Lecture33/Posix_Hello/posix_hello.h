#ifndef __POSIX_HELLO_H__
#define __POSIX_HELLO_H__

#include <fcntl.h>
#include <malloc.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define STOC "/stoc"    /*Название для очереди Server to Client*/
#define CTOS "/ctos"    /*Название для очереди Client to Server*/

void errExit(char *errstr);

#endif //__POSIX_HELLO_H__