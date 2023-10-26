#include "simple_vim.h"

WINDOW *wnd;
WINDOW *subwnd;

int main(int argc, char **argv) {
    int button, x, y;
    int fildes;
    char filename[20];
    char *writebuffer = NULL;
    char *temp = NULL;
    int index = 0;
    initscr();
    signal(SIGWINCH, sig_winch);        /*Обрабатываем сигнал изменения размера экрана*/
    start_screen();                     /*Выводим стартовое меню программы*/

    while (1) {
        switch (button = wgetch(curscr)) {
            case KEY_F(1):
                delwin(subwnd);
                delwin(wnd);
                echo();
                curs_set(1);
                keypad(stdscr, TRUE);
                refresh();
                filename_screen(filename);  /*Пользователь вводит название файла*/
                delwin(subwnd);
                delwin(wnd);
                border('~', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                fildes = case_file_open(fildes, filename);  /*Открытие файла и получение дескриптора*/
                writebuffer = calloc(1, 128);   /*Выделение начальной памяти для буффера записи*/
                refresh();
                wnd = newwin(1, 0, LINES - 1, 0);
                wprintw(wnd, "F2 - save and exit | F3 - exit without save");    /*Подсказка для пользователя как закрыть программу*/
                wrefresh(wnd);
                for (int i = 0; ; i++) {                
                    button = getch();
                    if (button == KEY_F(2)) {   /*Закрытие программы с сохранением изменений, внесенных пользователем*/
                        write(fildes, writebuffer, i);
                        fsync(fildes);
                        free(writebuffer);
                        break;
                    }
                    if (button == KEY_F(3)) {   /*Закрытие программы без сохранения изменений*/
                        free(writebuffer);
                        break;
                    }
                    if (button == '\n') {       /*Обработка переноса на новую строку*/
                        getyx(stdscr, y, x);
                        move(y + 1, -x);
                    }
                    if (i % 128 == 127) {       /*Выделение дополнительной памяти при переполнении буффера*/
                        temp = calloc(1, 128 * (i / 128 + 2));
                        strncpy(temp, writebuffer, strlen(writebuffer));
                        free(writebuffer);
                        writebuffer = temp;
                        temp = NULL;
                    }
                    writebuffer[i] = button;    /*Запись символов, введенных пользователем*/
                }
                break;
            case KEY_F(3):  /*Выход из программы со стартового меню*/
                break;
            default:        /*Если пользователь случайно вводит неверный символ на стартовом меню, программа не завершается*/
                break;
        }
        if (button == KEY_F(2) || button == KEY_F(3))   /*Выход из внешнего цикла, если пользователь нажал на кнопку для завершения программы*/
            break;
    }
    endwin();
    return 0;
}