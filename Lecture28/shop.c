#include "shop.h"

pthread_mutex_t mutex_first_shop = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_second_shop = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_third_shop = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_fourth_shop = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_fifth_shop = PTHREAD_MUTEX_INITIALIZER;

pthread_key_t threads_key;
pthread_once_t thread_once = PTHREAD_ONCE_INIT;
/*
Главная функция создает один поток, стартовая функция которого
loader_create, далее создает еще три потока, стартовая функция которых
customer_create.
После этого функция main ожидает завершения выполнения трех потоков
типа "покупатель", после них ожидает последний поток типа "погрузчик".
Как только "погрузчик" завершается, за ним завершается и функция main.
*/
int main() {
  pthread_t loader;
  pthread_t customer[3];
  int *status = NULL;
  int index = 0;
  pthread_create(&loader, NULL, (void *) loader_create, NULL);
  for (index; index < 3; index++) {
    pthread_create(&customer[index], NULL, (void *) customer_create, NULL);
  }
  for (index; index < 3; index++) {
    pthread_join(customer[index], (void **) &status);
  }
  pthread_join(loader, (void **) &status);
  return 0;
}