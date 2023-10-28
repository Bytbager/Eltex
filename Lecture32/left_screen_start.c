#include "my_mc.h"

WINDOW *left_main_scr;                  /*Создаем все нужные в будущем глобальные переменные*/
WINDOW *left_print_scr;                 /*для левой половины экрана*/
WINDOW *left_current_dir;
struct dirent **left_namelist = NULL;
char *left_temp_dir;

void left_screen_start() {
    left_temp_dir = calloc(1, 256);             /*Выделяем память под строку, в которой сохраняем*/
    left_temp_dir = getcwd(left_temp_dir, 256); /*путь к текущей директории*/
    int y, x;
    getmaxyx(curscr, y, x);
    left_main_scr = newwin(y, x / 2, 0, 0);     /*Создаем окна для левой части экрана*/
    getmaxyx(left_main_scr, y, x);
    wattron(left_main_scr, COLOR_PAIR(1));
    box(left_main_scr, 0, 0);
    wbkgd(left_main_scr, COLOR_PAIR(1));
    wrefresh(left_main_scr);
    left_current_dir = derwin(left_main_scr, 1, x - 2, 0, 1);
    wattron(left_current_dir, COLOR_PAIR(1) | A_REVERSE);
    left_print_scr = derwin(left_main_scr, y - 2, x - 2, 2, 1);
    wattron(left_print_scr, COLOR_PAIR(1));
    keypad(left_print_scr, TRUE);               /*Подключаем поддержку нестандартных клавиш*/
    wbkgd(left_print_scr, COLOR_PAIR(1));
    left_screen_logic();                        /*Переходим к логике левой половины экрана*/
}