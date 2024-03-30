#include "../server_type.h"

/*Программа создаёт 10 тысяч клиентов*/
int main() {
    pthread_t new_thread[10000];
    pthread_attr_t attr;

    if (pthread_attr_init(&attr) != 0)
        errExit("pthread_attr_init error!\n");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        errExit("pthread_attr_setdetachstate error!\n");

    for (int i = 0; i < 10000; i++) {
        pthread_create(&new_thread[i], &attr, (void *) client_thread_logic, (void *) i);
    }
    
    return 0;
}