#include "sort.h"

void rand_fill_array(int *array, unsigned int members) {
    srand(time(NULL));
    for (int i = 0; i < members; i++) {
        array[i] = rand()%5000;
    }
}