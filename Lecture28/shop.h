#ifndef __SHOP_H__
#define __SHOP_H__

#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOADER 1
#define CUSTOMER 2

#define FIRST_SHOP 1
#define SECOND_SHOP 2
#define THIRD_SHOP 3
#define FOURTH_SHOP 4
#define FIFTH_SHOP 5

struct shops {
    int first_shop_value;
    int second_shop_value;
    int third_shop_value;
    int fourth_shop_value;
    int fifth_shop_value;
};

struct thread_args {
    int thread_type;
    int need;
    int last_shop;
};

void loader_create();
void customer_create();
void create_thread_key();
void free_thread_key(void *args);
int shopping();

#endif //__SHOP_H__