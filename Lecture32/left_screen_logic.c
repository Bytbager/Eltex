#include "my_mc.h"

extern WINDOW *left_main_scr;           /*Указываем компилятору, что некоторые переменные*/
extern WINDOW *left_print_scr;          /*уже созданы в других файлах*/
extern WINDOW *left_current_dir;
extern struct dirent **left_namelist;
extern char *left_temp_dir;
int left_max_index = 0;

void left_screen_logic() {
    static int current_name = 0;        /*Создаем статическую переменную, которая хранит*/
    int index = 0;                      /*в себе текущую позицию на экране*/
    int exit_flag = 0;

    /*Сканируем текущую дикерторию, для вывода информации на экран*/
    left_max_index = scandir(left_temp_dir, &left_namelist, NULL, alphasort);

    while (1) {                         /*Далее входим в бесконечный цикл*/
        wclear(left_current_dir);
        wprintw(left_current_dir, "%s", left_temp_dir); /*Каждую итерацию цикла очищаем экран от текста*/
        wrefresh(left_current_dir);                     /*для отображения актуальной информации*/
        wclear(left_print_scr);
        wrefresh(left_print_scr);
        for (index = 0; index < left_max_index; index++) {  /*Выводим на экран файлы текущей директории*/
            if (index == current_name) {                    /*и подсвечиваем файл, на который указывает пользователь*/
                wattron(left_print_scr, A_REVERSE);
            }
            if (left_namelist[index]->d_type == 4)
                wprintw(left_print_scr, "/%s\n", left_namelist[index]->d_name);
            else
                wprintw(left_print_scr, " %s\n", left_namelist[index]->d_name);
            wrefresh(left_print_scr);
            if (index == current_name) {
                wattroff(left_print_scr, A_REVERSE);
            }
        }
        switch (wgetch(left_print_scr)) {                   /*Считываем клавиши, которые вводит пользователь*/
            
            case KEY_UP:                                    /*Клавиша вверх уменьшает позицию на экране на единицу*/
                if (current_name > 0) current_name--;       /*Это нужно для корректной подсветки файла, выбранного*/
                break;                                      /*пользователем*/

            case KEY_DOWN:                                  /*Клавиша вниз работает по такой же логике, как и клавиша*/
                                                            /*вверх, но увеличивает текущую позицию на экране*/
                if (current_name < left_max_index - 1) current_name++;
                break;
            case KEY_F(3):                                  /*При нажатии на клавишу F3, программа выходит из цикла*/
                exit_flag = 1;                              /*и попадает в функцию для очистки выделенной памяти*/
                break;

            case 9:                                         /*Символ с ASCII кодом 9 это TAB, при его нажатии*/
                wclear(left_print_scr);                     /*на экран выводятся файлы текущей директории без подсветки*/
                wrefresh(left_print_scr);                   /*далее программа попадает в функцию логики правой половины экрана*/
                for (index = 0; index < left_max_index; index++) {
                    if (left_namelist[index]->d_type == 4)
                        wprintw(left_print_scr, "/%s\n", left_namelist[index]->d_name);
                    else
                        wprintw(left_print_scr, " %s\n", left_namelist[index]->d_name);
                    wrefresh(left_print_scr);
                }
                right_screen_logic();
                break;
            
            case '\n':                                      /*При нажатии на клавишу ENTER, программа проверяет*/
                                                            /*является ли текущая позиция на экране директорией*/
                                                            /*и если это так, то она сканирует её, выводит на экран*/
                                                            /*и меняет текущий путь*/
                if (left_namelist[current_name]->d_type == 4) {
                    if (strcmp("..", left_namelist[current_name]->d_name) == 0) {
                        for (int i = strlen(left_temp_dir);; i--) {
                            if (left_temp_dir[i] == '/') {
                                left_temp_dir[i] = '\0';
                                break;
                            }
                            left_temp_dir[i] = '\0';
                        }
                    } else if (strcmp(".", left_namelist[current_name]->d_name) == 0) {
                        break;
                    } else {
                        strcat(left_temp_dir, "/");
                        strncat(left_temp_dir, left_namelist[current_name]->d_name,
                                strlen(left_namelist[current_name]->d_name));
                    }
                    for (int i = 0; i < left_max_index; i++) {
                        free(left_namelist[i]);
                        left_namelist[i] = NULL;
                    }
                    free(left_namelist);
                    left_namelist = NULL;
                    left_max_index = scandir(left_temp_dir, &left_namelist, NULL, alphasort);
                    if (left_max_index == -1) {
                        perror("scandir error\n");
                        exit(EXIT_FAILURE);
                    }
                    current_name = 0;
                }
                break;
            default:        /*При нажатии на любую другую клавишу, программа попадает на следующую итерацию цикла*/
                break;
        }
        if (exit_flag == 1) break;  /*Реализация выхода из бесконечного цикла*/
    }
    my_mc_free_exit();      /*Функция для очистки выделенной памяти*/
}