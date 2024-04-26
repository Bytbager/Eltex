#include "sort.h"

unsigned int partition(int **array, unsigned int lowest, unsigned int highest);

int quick_sort(int **array, unsigned int lowest, unsigned int highest)  {
    int *p_array = *array, **pp_array = &p_array;

    if (lowest < highest) {
        unsigned int pivot;
        pivot = partition(pp_array, lowest, highest);
        if (pivot != 0) {
            quick_sort(pp_array, lowest, pivot - 1);
            quick_sort(pp_array, pivot + 1, highest);
        }
    }

    return 0;
}

unsigned int partition(int **array, unsigned int lowest, unsigned int highest) {
    unsigned int pivot, j;
    int temp;

    pivot = (*array)[highest];
    j = lowest;

    for (int i = lowest; i <= highest - 1; i++) {
        if ((*array)[i] <= pivot) {
            temp = (*array)[j];
            (*array)[j] = (*array)[i];
            (*array)[i] = temp;
            j++;
        }
    }

    temp = (*array)[j];
    (*array)[j] = (*array)[highest];
    (*array)[highest] = temp;

    return j;
}