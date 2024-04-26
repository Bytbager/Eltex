#include "sort.h"

int build_max_heap(int **array, unsigned int members);
int heapify_down(int **array, unsigned int array_size, unsigned int index);

int heap_sort(int **array, unsigned int members) {
    int *p_array = *array, **pp_array = &p_array;
    unsigned int index = members;
    int temp;

    build_max_heap(pp_array, members);

    while (index >= 1) {
        index--;
        temp = (*array)[0];
        (*array)[0] = (*array)[index];
        (*array)[index] = temp;
        heapify_down(pp_array, index, 0);
    }

    return 0;
}

int build_max_heap(int **array, unsigned int members) {
    int index = members / 2 - 1;
    int *p_array = *array, **pp_array = &p_array;

    while (index >= 0) {
        heapify_down(pp_array, members, index);
        index--;
    }

    return 0;
}

int heapify_down(int **array, unsigned int array_size, unsigned int index) {
    unsigned int left, right, largest;
    int temp;

    while (index < array_size) {
        left = 2 * (index + 1) - 1;
        right = 2 * (index + 1);
        largest = index;

        if (left < array_size && (*array)[left] > (*array)[largest])
            largest = left;
        if (right < array_size && (*array)[right] > (*array)[largest])
            largest = right;

        if (largest != index) {
            temp = (*array)[largest];
            (*array)[largest] = (*array)[index];
            (*array)[index] = temp;
            index = largest;
        } else break;
    }

    return 0;
}