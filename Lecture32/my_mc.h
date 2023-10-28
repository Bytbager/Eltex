#ifndef __MY_MC_H__
#define __MY_MC_H__

#include <dirent.h>
#include <malloc.h>
#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

void sig_winch(int signo);
void left_screen_start(void);
void left_screen_logic(void);
void right_screen_start(void);
void right_screen_logic(void);
void my_mc_free_exit(void);

#endif  //__MY_MC_H__