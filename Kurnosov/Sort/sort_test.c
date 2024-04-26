#include "sort.h"
    
extern char *optarg;

int main(int argc, char **argv) {
    int opt, members = 1000, time_flag = 0, print_flag = 0;
    int *array = malloc(members * sizeof(int));
    time_t start_time, end_time, result_time;
    struct tm *sort_time;
    int *p_array = array, **pp_array = &p_array;

    if (argc == 1) {
        usage(argv[0]);
        free(array);
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "M:siqmHchp")) != -1) {
        switch (opt) {
            case 'h':
                usage(argv[0]);
                free(array);
                exit(EXIT_SUCCESS);
            case 'M':
                members = atoi(optarg);
                array = realloc(array, members * sizeof(int));
                p_array = array;
                break;
            case 'p':
                print_flag = 1;
                break;
            case 's':
                rand_fill_array(array, members);
                start_time = time(NULL);
                selection_sort(array, members);
                end_time = time(NULL);
                break;
            case 'i':
                rand_fill_array(array, members);
                start_time = time(NULL);
                insertion_sort(array, members);
                end_time = time(NULL);
                break;
            case 'q':
                rand_fill_array(array, members);
                start_time = time(NULL);
                quick_sort(pp_array, 0, members - 1);
                end_time = time(NULL);
                break;
            case 'm':
                rand_fill_array(array, members);
                start_time = time(NULL);
                merge_sort(pp_array, 0, members - 1);
                end_time = time(NULL);
                break;
            case 'H':
                rand_fill_array(array, members);
                start_time = time(NULL);
                heap_sort(pp_array, members);
                end_time = time(NULL);
                break;
            case 'c':
                rand_fill_array(array, members);
                start_time = time(NULL);
                counting_sort(pp_array, members, 5000);
                end_time = time(NULL);
                break;
            case '?':
                usage(argv[0]);
                free(array);
                exit(EXIT_FAILURE);
        }
    }

    if (print_flag == 1) print_array(array, members);

    result_time = end_time - start_time;
    sort_time = gmtime(&result_time);
    printf("sort time: %d mins %d secs\n", sort_time->tm_min, sort_time->tm_sec);

    free(array);
    exit(EXIT_SUCCESS);
}