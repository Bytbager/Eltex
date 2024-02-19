#include "../server_type.h"

int main() {
    pthread_t new_thread[1000];
    int number, *status;
    for (int i = 0; i < 10000; i++) {
        number = i;
        pthread_create(&new_thread[i], NULL, client_thread_logic, &number);
        pthread_join(new_thread[i], (void **) &status);
    }
    return 0;
}