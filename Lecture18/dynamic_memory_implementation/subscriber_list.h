#ifndef __SUBSCRIBER_LIST_H__
#define __SUBSCRIBER_LIST_H__

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>

struct People {
    char *name;
    char *surname;
    char *phone_number;
};

#define OK 0
#define ERROR 1

int new_subscriber(int *subscriber_count, struct People *list);
int delete_subscriber(int *subscriber_count, struct People *list);
int show_subscriber_list(int *subscriber_count, struct People *list);
int quit_program(int *subscribers_count, struct People *list, int error);

#endif //__SUBSCRIBER_LIST_H__