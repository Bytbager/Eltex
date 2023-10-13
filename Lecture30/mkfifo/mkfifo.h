#ifndef __MKFIFO_H__
#define __MKFIFO_H__

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SERVER_FIFO "./server_fifo"
#define CLIENT_FIFO "./client_fifo"

#endif //__MKFIFO_H__