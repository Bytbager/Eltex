#ifndef SORT_H
#define SORT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*Utils for sort_test program*/
void print_array(int *array, unsigned int members);
void rand_fill_array(int *array, unsigned int members);
void usage(const char *prog_name);

/*Sort methods*/
int counting_sort(int **array, unsigned int members, unsigned int max_number);
int heap_sort(int **array, unsigned int members);
int insertion_sort(int *array, unsigned int members);
int merge_sort(int **array, unsigned int lowest, unsigned int highest);
int selection_sort(int *array, unsigned int members);
int quick_sort(int **array, unsigned int lowest, unsigned int highest);

#endif //SORT_H