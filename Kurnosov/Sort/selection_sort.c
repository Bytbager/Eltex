#include "sort.h"

int selection_sort(int *array, unsigned int members) {
    int minindex, temp;

    for (int i = 0; i < members - 1; i++) {
        minindex = i;

        for(int j = i + 1; j < members; j++) {
            if (array[j] < array[minindex])
                minindex = j;
        }

        if (minindex != i) {
            temp = array[i];
            array[i] = array[minindex];
            array[minindex] = temp;
        }
    }

    return 0;
}