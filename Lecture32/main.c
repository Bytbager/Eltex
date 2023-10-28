#include "my_mc.h"

int main() {
    initscr();                      /*Инициализируем экран для библиотеки ncurses*/
    signal(SIGWINCH, sig_winch);    /*Обрабатываем сигнал изменения размера экрана*/
    start_color();                  /*Подключаем поддержку цвета*/
    curs_set(FALSE);                /*Отключаем отображение курсора*/
    refresh();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  /*Инициализируем цветовую пару, для дальнейшего использования*/
    right_screen_start();           /*Начинаем отображение правой половины экрана*/
    return 0;
}