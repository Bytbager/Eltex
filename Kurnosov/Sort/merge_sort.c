#include "sort.h"

int merge(int **array, unsigned int lowest, unsigned int middle, unsigned int highest);

int merge_sort(int **array, unsigned int lowest, unsigned int highest) {
    unsigned int middle;
    int *p_array = *array, **pp_array = &p_array;

    if (lowest < highest) {
        middle = (lowest + highest) / 2;
        merge_sort(pp_array, lowest, middle);
        merge_sort(pp_array, middle + 1, highest);
        merge(pp_array, lowest, middle, highest);
    }

    return 0;
}

int merge(int **array, unsigned int lowest, unsigned int middle, unsigned int highest) {
    unsigned int size = highest - lowest + 1;
    int *array_copy = malloc(sizeof(int) * size);
    unsigned int first_left, first_right, mid_copy, index = lowest;

    for (int i = 0; i < size; i++) {
        array_copy[i] = (*array)[index];
        index++;
    }

    first_left = 0;
    mid_copy = (size - 1) / 2;
    first_right = mid_copy + 1;
    index = lowest;

    while (first_left <= mid_copy && first_right <= size - 1) {
        if (array_copy[first_left] <= array_copy[first_right]) {
            (*array)[index] = array_copy[first_left];
            first_left++;
        } else {
            (*array)[index] = array_copy[first_right];
            first_right++;
        }
        index++;
    }

    while (first_left <= mid_copy) {
        (*array)[index] = array_copy[first_left];
        first_left++;
        index++;
    }

    while (first_right <= size - 1) {
        (*array)[index] = array_copy[first_right];
        first_right++;
        index++;
    }

    free(array_copy);

    return 0;
}