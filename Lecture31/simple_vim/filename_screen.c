#include "simple_vim.h"

extern WINDOW *wnd;
extern WINDOW *subwnd;

/*
Функция запрашивает у пользователя ввод названия
файла, который он хочет открыть или создать.
*/
void filename_screen(char *filename) {
    int y, x;
    getmaxyx(curscr, y, x);
    wnd = newwin(y / 3, x / 3, y / 3, x / 3);
    box(wnd, 0, 0);
    getmaxyx(wnd, y, x);
    mvwprintw(wnd, (y / 3), (x / 3), "Choose filename(max 20 symbols).\n");
    wrefresh(wnd);
    mvwgetstr(wnd, y / 3 + 1, x / 3, filename);
}