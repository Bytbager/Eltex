#ifndef __MY_CHAT_H__
#define __MY_CHAT_H__

#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <mqueue.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#define SERVTOCLI "/server_to_client"
#define CLITOSERV "/client_to_server"
#define SERVTOUSERTHREAD "/server_to_user_thread"
#define SERVTOMSGTHREAD "/server_to_message_thread"
#define CLITOMSGHISTTHREAD "/client_to_msg_hist_thread"
#define CLITOMSGWRTHREAD "/client_to_msg_wr_thread"
#define CLITOUSERSTHREAD "/clien_to_users_thread"

struct User {
    pid_t pid;
    mqd_t mqds;
    char nickname[16];
};

struct user_list {
    struct User user;
    struct user_list *next;
};

struct msg_create_args {
    int *read_pipe;
    mqd_t *write_mqds;
};

enum PRIO {
    MESSAGE = 1,
    SERVER_RECEIVED_DELETION_REQUEST = 29,
    DELETED_USER = 30,
    NEW_USER = 31
};

void errExit(char *errstr);
void sig_winch(int signo);
void users_thread(mqd_t *write_mqds);
int add_user(struct user_list **root, struct User **new_user);
int print_list(struct user_list *root, WINDOW *win);
int delete_user(struct user_list **root, struct User **exited_user);
int create_mq_for_client(struct user_list **root, struct User **new_user);
int delete_client_mq(struct user_list **root, struct User **exited_user);
void message_thread(void);
void message_history_thread(int *read_pipe);
void user_list_thread(int *read_pipe);
void message_create_thread(mqd_t *write_mqds);
void start_screen(struct User *me);

#endif //__MY_CHAT_H__