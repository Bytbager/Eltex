#include "../my_chat.h"

WINDOW *start_screen_win;
/*
Функция выводит стартовое меню программы.
*/
void start_screen(struct User *me) {
    int y, x;
    keypad(curscr, TRUE);
    cbreak();
    curs_set(0);
    getmaxyx(curscr, y, x);
    start_screen_win = newwin(y / 3, x / 3, y / 3, x / 3);
    box(start_screen_win, 0, 0);
    getmaxyx(start_screen_win, y, x);
    wattron(start_screen_win, COLOR_PAIR(1));
    wbkgd(start_screen_win, COLOR_PAIR(1));
    mvwprintw(start_screen_win, (y / 3), (x / 3), "Enter your nickname:");
    mvwprintw(start_screen_win, (y / 3) + 1, (x / 3), "(Maximum 16 symbols)");
    wrefresh(start_screen_win);
    mvwgetnstr(start_screen_win, (y / 3) * 2, x / 3, me->nickname, 16);
    (*me).pid = getpid();
    delwin(start_screen_win);
    start_screen_win = NULL;
    clear();
    refresh();
}