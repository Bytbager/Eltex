#include "../my_chat_shmem.h"

struct user me;

int main() {
    pthread_t msg_hist_thread, usr_thread, msg_create_thread;
    void *res;

    /*Инициализируем библиотеку ncurses*/

    initscr();
    signal(SIGWINCH, sig_winch);
    start_color();
    cbreak();
    curs_set(FALSE);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    bkgd(COLOR_PAIR(1));
    refresh();

    /*Просим пользователя ввести ник*/

    memset(&me, 0, sizeof(struct user));
    start_screen(&me);

    /*Создаём 3 потока:
    первый отвечает за отображение списка пользователей,
    второй за список сообщений,
    третий за ввод сообщения пользователем*/

    if (pthread_create(&usr_thread, NULL, (void *) user_list_thread, NULL) != 0)
        errExit("pthread_create usr_thread error!\n");
    if (pthread_create(&msg_hist_thread, NULL, (void *) message_history_thread, NULL) != 0)
        errExit("pthread_create msg_hist thread error!\n");
    if (pthread_create(&msg_create_thread, NULL, (void *) message_create_thread, NULL) != 0)
        errExit("pthread_create msg_create_thread error!\n");

    /*Пользователь может выйти из чата путём написания сообщения
    "exit", если это происходит, поток, отвечающий за ввод, завершается
    и присоединяется к главному потоку*/

    if (pthread_join(msg_create_thread, NULL) != 0)
        errExit("pthread_join msg_create_thread error!\n");
    
    /*Выключаем ncurses*/

    endwin();
    
    /*Отменяем поток, отвечающий за список пользователей*/

    if (pthread_cancel(usr_thread) != 0)
        errExit("pthread_cancel user_thread error!\n");
    if (pthread_join(usr_thread, &res) != 0)
        errExit("pthread_join error!\n");
    if (res == PTHREAD_CANCELED)
        printf("user_thread canceled!\n"); 

    /*Отменяем поток, отвечающий за список сообщений*/

    if (pthread_cancel(msg_hist_thread) != 0)
        errExit("pthread_cancel user_thread error!\n");
    if (pthread_join(msg_hist_thread, &res) != 0)
        errExit("pthread_join error!\n");
    if (res == PTHREAD_CANCELED)
        printf("msg_hist_thread canceled!\n"); 
        
    return 0;
}