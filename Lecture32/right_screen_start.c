#include "my_mc.h"

WINDOW *right_main_scr;     /*Создаем все нужные глобальные переменные*/
WINDOW *right_print_scr;    /*для их дальнейшего использования*/
WINDOW *right_current_dir;
struct dirent **right_namelist = NULL;
char *right_temp_dir;

void right_screen_start() {
    int max_index = 0;
    right_temp_dir = calloc(1, 256);                /*Выделяем память под строку, в которой будет храниться*/
    right_temp_dir = getcwd(right_temp_dir, 256);   /*текущий путь к отображаемой на экране директории*/
                                                    /*и сразу же получаем начальный путь*/
    int y, x;
    getmaxyx(curscr, y, x);                         /*Получаем текущую ширину и высоту экрана для создания окон*/
    right_main_scr = newwin(y, x / 2, 0, x / 2);    /*Далее создаем окна правой половины экрана*/
    getmaxyx(right_main_scr, y, x);
    wattron(right_main_scr, COLOR_PAIR(1));
    box(right_main_scr, 0, 0);
    wbkgd(right_main_scr, COLOR_PAIR(1));
    wrefresh(right_main_scr);
    right_current_dir = derwin(right_main_scr, 1, x - 2, 0, 1);
    wattron(right_current_dir, COLOR_PAIR(1) | A_REVERSE);
    right_print_scr = derwin(right_main_scr, y - 2, x - 2, 2, 1);
    wattron(right_print_scr, COLOR_PAIR(1));
    keypad(right_print_scr, TRUE);                  /*Подключаем поддержку нестандартных клавиш*/
    wbkgd(right_print_scr, COLOR_PAIR(1));

    max_index = scandir(right_temp_dir, &right_namelist, NULL, alphasort);  /*Получаем список файлов в текущей*/
    wprintw(right_current_dir, "%s", right_temp_dir);                       /*директории и выводим их на экран*/
    wrefresh(right_current_dir);
    for (int i = 0; i < max_index; i++) {
        if (right_namelist[i]->d_type == 4)
            wprintw(right_print_scr, "/%s\n", right_namelist[i]->d_name);
        else
            wprintw(right_print_scr, " %s\n", right_namelist[i]->d_name);
        wrefresh(right_print_scr);
    }
    left_screen_start();    /*Далее переходим к инициализации левой половины экрана*/
}