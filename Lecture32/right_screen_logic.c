#include "my_mc.h"

extern WINDOW *right_main_scr;
extern WINDOW *right_print_scr;
extern WINDOW *right_current_dir;
extern struct dirent **right_namelist;
extern char *right_temp_dir;
int right_max_index = 0;
/*
Функция реализована идентично логике левой половины экрана
для получения большей информации посмотрите файл left_screen_logic.c
*/
void right_screen_logic() {
    int index = 0;
    int exit_flag = 0;
    int new_dir = 0;
    static int current_name = 0;
    right_max_index = scandir(right_temp_dir, &right_namelist, NULL, alphasort);
    while (1) {
        if (exit_flag == 1) break;
        wclear(right_current_dir);
        wprintw(right_current_dir, "%s", right_temp_dir);
        wrefresh(right_current_dir);
        wclear(right_print_scr);
        wrefresh(right_print_scr);
        for (index = 0; index < right_max_index; index++) {
            if (index == current_name) {
                wattron(right_print_scr, A_REVERSE);
            }
            if (right_namelist[index]->d_type == 4)
                wprintw(right_print_scr, "/%s\n", right_namelist[index]->d_name);
            else
                wprintw(right_print_scr, " %s\n", right_namelist[index]->d_name);
            wrefresh(right_print_scr);
            if (index == current_name) {
                wattroff(right_print_scr, A_REVERSE);
            }
        }
        switch (wgetch(right_print_scr)) {
            case KEY_UP:
                if (current_name > 0) current_name--;
                break;
            case KEY_DOWN:
                if (current_name < right_max_index - 1) current_name++;
                break;
            case KEY_F(3):
                exit_flag = 1;
                break;
            case 9:
                wclear(right_print_scr);
                wrefresh(right_print_scr);
                for (index = 0; index < right_max_index; index++) {
                    if (right_namelist[index]->d_type == 4)
                        wprintw(right_print_scr, "/%s\n", right_namelist[index]->d_name);
                    else
                        wprintw(right_print_scr, " %s\n", right_namelist[index]->d_name);
                    wrefresh(right_print_scr);
                }
                left_screen_logic();
                break;
            case '\n':
                if (right_namelist[current_name]->d_type == 4) {
                    if (strcmp("..", right_namelist[current_name]->d_name) == 0) {
                        for (int i = strlen(right_temp_dir);; i--) {
                            if (right_temp_dir[i] == '/') {
                                right_temp_dir[i] = '\0';
                                break;
                            }
                            right_temp_dir[i] = '\0';
                        }
                    } else if (strcmp(".", right_namelist[current_name]->d_name) == 0) {
                        break;
                    } else {
                        strcat(right_temp_dir, "/");
                        strncat(right_temp_dir, right_namelist[current_name]->d_name,
                                strlen(right_namelist[current_name]->d_name));
                    }
                    for (int i = 0; i < right_max_index; i++) {
                        free(right_namelist[i]);
                        right_namelist[i] = NULL;
                    }
                    free(right_namelist);
                    right_namelist = NULL;
                    right_max_index = scandir(right_temp_dir, &right_namelist, NULL, alphasort);
                    if (right_max_index == -1) {
                        perror("scandir error\n");
                        exit(EXIT_FAILURE);
                    }
                    current_name = 0;
                }
                break;
            default:
                break;
        }
    }
    my_mc_free_exit();
}