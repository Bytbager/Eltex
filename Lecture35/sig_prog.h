#ifndef __SIG_PROG_H__
#define __SIG_PROG_H__

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void errExit(char *errstr);
void handler(int signum);

#endif //__SIG_PROG_H__