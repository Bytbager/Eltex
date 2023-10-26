#include "simple_vim.h"

extern WINDOW *wnd;
extern WINDOW *subwnd;

/*
Функция выводит стартовое меню программы.
*/
void start_screen() {
    int y, x;
    keypad(curscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
    getmaxyx(curscr, y, x);
    wnd = newwin(y / 3, x / 3, y / 3, x / 3);
    box(wnd, 0, 0);
    getmaxyx(wnd, y, x);
    mvwprintw(wnd, (y / 3), (x / 3), "F1 - open or create new file.");
    mvwprintw(wnd, (y / 3) * 2, x / 3, "F3 - exit programm.");
    wrefresh(wnd);
}