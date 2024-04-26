#include "sort.h"

int insertion_sort(int *array, unsigned int members) {
    int key;
    int i = 1, j;

    for (i; i < members; i++) {
    
        key = array[i];
        j = i - 1;

        while (j > -1 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    
    }

    return 0;
}