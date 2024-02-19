#include "../my_chat.h"

/*
Функция обрабатывает сигнал об изменении размера экрана.
Она нужна для того, чтобы программа не завершалась при
получении этого сигнала.
*/
void sig_winch(int signo) {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
    resizeterm(size.ws_row, size.ws_col);
}