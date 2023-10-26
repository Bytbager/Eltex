#ifndef __SIMPLE_VIM_H__
#define __SIMPLE_VIM_H__

#include <ncurses.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

void sig_winch(int signo);
void start_screen(void);
void filename_screen(char *filename);
int case_file_open(int fildes, char *filename);

#endif //__SIMPLE_VIM_H__