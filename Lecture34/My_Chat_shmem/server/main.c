#include "../my_chat_shmem.h"

int main() {
    pthread_t msg_thread, usr_thread;

    /*Создаём 2 потока - один создаст сегмент
    разделяемой памяти для списка пользователей,
    другой - для списка сообщений*/

    if (pthread_create(&usr_thread, NULL, (void *) users_thread, NULL) != 0)
        errExit("pthread_create usr_thread error!\n");
    if (pthread_create(&msg_thread, NULL, (void *) message_thread, NULL) != 0)
        errExit("pthread_create msg_thread error!\n");

    while (1) {}

    return 0;
}