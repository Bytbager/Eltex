#include "shop.h"

extern pthread_mutex_t mutex_first_shop;
extern pthread_mutex_t mutex_second_shop;
extern pthread_mutex_t mutex_third_shop;
extern pthread_mutex_t mutex_fourth_shop;
extern pthread_mutex_t mutex_fifth_shop;

extern pthread_key_t threads_key;

struct shops Shops = {1000, 1000, 1000, 1000, 1000};
int customers_left = 3;
/*
Функция в бесконечном цикле имитирует сеть из 5 магазинов,
в которые заходят потоки типа "погрузчик" и "покупатель".
В каждом из магазинов может находиться не более 1 потока
одновременно, это достигается путем использования примитивов
синхронизации. Когда поток заходит в свободный магазин,
он блокирует его для других потоков.

Поток типа "погрузчик" при заходе в магазин добавляет к
текущему значению единиц потребности в магазине еще 500.
После этого "погрузчик" засыпает на 2 секунды, далее
пробуждается и пытается попасть в один из оставшихся
магазинов, чтобы повторить операцию снова.

Поток типа "покупатель" при заходе в магазин приобретает
все единицы потребности, которые в нем имеются. После
этого отправляется в сон на 2 секундны, далее
пробуждается и пытается попасть в один из оставшихся
магазинов, чтобы повторить операцию снова.

Со старта в каждом магазине есть 1000 единиц потребности и
у каждого потока типа "покупатель" есть по 10000 единиц
незакрытой потребности.

После посещения любым потоком любого из магазинов, в параметре
потока args->last_shop указывается номер этого магазина.
Это используется для избежания ситуаций, в которых поток будет
много раз подряд попадать в один и тот же магазин.

Цель "покупателя" закрыть все свои потребности, после этого
он выходит из бесконечного цикла с помощью библиотечной функции
break и возвращается в функцию main.

Цель "погрузчика" закрыть потребности всех "покупателей", то
есть, когда "покупателей" не останется, "погрузчик" также 
выходит из бесконечного цикла и возвращается в функцию main.

Входные данные отсутствуют.
Функция возвращает 0 после успешного завершения.
*/
int shopping() {
    struct thread_args *args = NULL;
    args = pthread_getspecific(threads_key);
    pthread_mutex_t mutex_customer = PTHREAD_MUTEX_INITIALIZER;
    while (1) {
        if (pthread_mutex_trylock(&mutex_first_shop) == 0 && args->last_shop != FIRST_SHOP) {
            if (args->thread_type == LOADER) {
                Shops.first_shop_value += 500;
                printf("Loader came in first shop\n"
                        "and added 500 shop value\n"
                        "First shop value = %d\n"
                        "Loader fell asleep for 2 secs\n\n", Shops.first_shop_value);
                sleep(2);
            } else if (args->thread_type == CUSTOMER) {
                args->need = args->need - Shops.first_shop_value;
                printf("Customer came in first shop\n"
                        "and got all shop value = %d\n", Shops.first_shop_value);
                Shops.first_shop_value = 0;
                printf("Customer need = %d\n"
                        "Customer fell asleep for 2 secs\n\n", args->need);
                sleep(2);
            }
            args->last_shop = FIRST_SHOP;
            pthread_mutex_unlock(&mutex_first_shop);
        }
        if (pthread_mutex_trylock(&mutex_second_shop) == 0 && args->last_shop != SECOND_SHOP) {
            if (args->thread_type == LOADER) {
                Shops.second_shop_value += 500;
                printf("Loader came in second shop\n"
                        "and added 500 shop value\n"
                        "Second shop value = %d\n"
                        "Loader fell asleep for 2 secs\n\n", Shops.second_shop_value);
                sleep(2);
            } else if (args->thread_type == CUSTOMER) {
                args->need = args->need - Shops.second_shop_value;
                printf("Customer came in second shop\n"
                        "and got all shop value = %d\n", Shops.second_shop_value);
                Shops.second_shop_value = 0;
                printf("Customer need = %d\n"
                        "Customer fell asleep for 2 secs\n\n", args->need);
                sleep(2);
            }
            args->last_shop = SECOND_SHOP;
            pthread_mutex_unlock(&mutex_second_shop);
        }
        if (pthread_mutex_trylock(&mutex_third_shop) == 0 && args->last_shop != THIRD_SHOP) {
            if (args->thread_type == LOADER) {
                Shops.third_shop_value += 500;
                printf("Loader came in third shop\n"
                        "and added 500 shop value\n"
                        "Third shop value = %d\n"
                        "Loader fell asleep for 2 secs\n\n", Shops.third_shop_value);
                sleep(2);
            } else if (args->thread_type == CUSTOMER) {
                args->need = args->need - Shops.third_shop_value;
                printf("Customer came in third shop\n"
                        "and got all shop value = %d\n", Shops.third_shop_value);
                Shops.third_shop_value = 0;
                printf("Customer need = %d\n"
                        "Customer fell asleep for 2 secs\n\n", args->need);
                sleep(2);
            }
            args->last_shop = THIRD_SHOP;
            pthread_mutex_unlock(&mutex_third_shop);
        }
        if (pthread_mutex_trylock(&mutex_fourth_shop) == 0 && args->last_shop != FOURTH_SHOP) {
            if (args->thread_type == LOADER) {
                Shops.fourth_shop_value += 500;
                printf("Loader came in fourth shop\n"
                        "and added 500 shop value\n"
                        "Fourth shop value = %d\n"
                        "Loader fell asleep for 2 secs\n\n", Shops.fourth_shop_value);
                sleep(2);
            } else if (args->thread_type == CUSTOMER) {
                args->need = args->need - Shops.fourth_shop_value;
                printf("Customer came in fourth shop\n"
                        "and got all shop value = %d\n", Shops.fourth_shop_value);
                Shops.fourth_shop_value = 0;
                printf("Customer need = %d\n"
                        "Customer fell asleep for 2 secs\n\n", args->need);
                sleep(2);
            }
            args->last_shop = FOURTH_SHOP;
            pthread_mutex_unlock(&mutex_fourth_shop);            
        }
        if (pthread_mutex_trylock(&mutex_fifth_shop) == 0 && args->last_shop != FIFTH_SHOP) {
            if (args->thread_type == LOADER) {
                Shops.fifth_shop_value += 500;
                printf("Loader came in fifth shop\n"
                        "and added 500 shop value\n"
                        "Fifth shop value = %d\n"
                        "Loader fell asleep for 2 secs\n\n", Shops.fifth_shop_value);
                sleep(2);
            } else if (args->thread_type == CUSTOMER) {
                args->need = args->need - Shops.fifth_shop_value;
                printf("Customer came in fifth shop\n"
                        "and got all shop value = %d\n", Shops.fifth_shop_value);
                Shops.fifth_shop_value = 0;
                printf("Customer need = %d\n"
                        "Customer fell asleep for 2 secs\n\n", args->need);
                sleep(2);
            }
            args->last_shop = FIFTH_SHOP;
            pthread_mutex_unlock(&mutex_fifth_shop);            
        }
        if (args->thread_type == CUSTOMER && args->need <= 0) {
            pthread_mutex_lock(&mutex_customer);
            customers_left -= 1;
            pthread_mutex_unlock(&mutex_customer);
            break;
        } else if (args->thread_type == LOADER && customers_left == 0) {
            break;
        }
    }
    return 0;
}