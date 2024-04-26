#include "sort.h"

void print_array(int *array, unsigned int members) {
    for (int i = 0; i < members; i++) {
        if ((i + 1) % 20 == 0) printf("%5d |\n", array[i]);
        else printf("%5d | ", array[i]);
    }
}