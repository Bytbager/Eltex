#include "sort.h"

int counting_sort(int **array, unsigned int members, unsigned int max_number) {
    int *count_array = malloc(sizeof(int) * max_number);
    memset(count_array, 0, sizeof(int) * max_number);

    unsigned int count = 0;

    for (int i = 0; i < members; i++)
        count_array[(*array)[i]]++;

    for (int i = 1; i < max_number; i++)
        count_array[i] = count_array[i] + count_array[i - 1];

    for (int i = 0; i < members; i++) {
        while (i == count_array[count])
            count++;
        (*array)[i] = count;
    }

    free(count_array);

    return 0;
}