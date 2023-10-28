#include "my_mc.h"

extern WINDOW *left_main_scr;
extern WINDOW *left_print_scr;
extern WINDOW *left_current_dir;
extern struct dirent **left_namelist;
extern char *left_temp_dir;
extern int left_max_index;

extern WINDOW *right_main_scr;
extern WINDOW *right_print_scr;
extern WINDOW *right_current_dir;
extern struct dirent **right_namelist;
extern char *right_temp_dir;
extern int right_max_index;
/*
Функция очищает всю выделенную ранее память
и завершает работу всей программы.
*/
void my_mc_free_exit() {
    delwin(left_current_dir);
    delwin(right_current_dir);
    delwin(left_print_scr);
    delwin(right_print_scr);
    delwin(left_main_scr);
    delwin(right_main_scr);
    endwin();
    for (int i = 0; i < left_max_index; i++) {
        free(left_namelist[i]);
        left_namelist[i] = NULL;
    }
    free(left_temp_dir);
    left_temp_dir = NULL;
    for (int i = 0; i < right_max_index; i++) {
        free(right_namelist[i]);
        right_namelist[i] = NULL;
    }
    free(right_temp_dir);
    right_temp_dir = NULL;
    exit(EXIT_SUCCESS);
}