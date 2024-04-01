#include "../my_chat.h"

pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;

void user_list_thread(int *read_pipe) {
    WINDOW *main_win, *print_win;    
    struct User *new_user = NULL;
    struct user_list *root = NULL, *tmp = NULL;
    char buff[256];
    int x, y;
    
    pthread_mutex_lock(&screen);
    new_user = calloc(1, sizeof(struct User));
    if (new_user == NULL)
        errExit("new_user calloc error!\n");

    root = calloc(1, sizeof(struct user_list));
    if (root == NULL)
        errExit("root calloc error!\n");
    pthread_mutex_unlock(&screen);

    tmp = root;

    /*Создаём окна:
    main_win - отображает границы окна
    print_win - окно, в котором будет отображаться печать пользователя*/

    getmaxyx(curscr, y, x);
    main_win = newwin(35, 20, 0, 0);
    wattron(main_win, COLOR_PAIR(1));
    box(main_win, 0, 0);
    wbkgd(main_win, COLOR_PAIR(1));
    wrefresh(main_win);

    getmaxyx(main_win, y, x);
    print_win = derwin(main_win, y - 2, x - 2, 1, 1);
    wattron(print_win, COLOR_PAIR(1));
    wbkgd(print_win, COLOR_PAIR(1));
    wrefresh(print_win);

    int rc = 0;

    /*Входим в бесконечный цикл получения сообщений
    от главного потока*/
    while (1) {
        memset(new_user, 0, sizeof(struct User));

        /*Слушаем канал между нашим потоком и главным*/
        rc = read(*read_pipe, new_user, sizeof(struct User));
        if ( rc == -1)
            errExit("user_list read error!\n");
        else if (rc > 0) {

            /*Если получили структуру пользователя со значением
            DELETED_USER в его дескрипторе, то удаляем пользователя
            из списка и обновляем информацию на экране*/
            if (new_user->mqds == DELETED_USER) {
                delete_user(&root, &new_user);
                pthread_mutex_lock(&screen);
                print_list(root, print_win);
                pthread_mutex_unlock(&screen);
            }
            
            /*Если получили структуру пользователя со значением
            SERVER_RECEIVED_DELETION_REQUEST в дескрипторе, это
            говорит о том, что наш пользователь вышел из программы.
            Закрываем окна, очищаем память и завершаем поток*/
            else if (new_user->mqds == SERVER_RECEIVED_DELETION_REQUEST) {
                pthread_mutex_lock(&screen);
                delwin(print_win);
                delwin(main_win);
                free(new_user);
                if (root != NULL)
                free(root);
                pthread_mutex_unlock(&screen);
                pthread_exit(NULL);
            }
            
            /*Если поступило любое другое сообщение, это говорит
            о том, что появился новый пользователь, добавляем его в
            список и обновляем информацию на экране*/
            else {
                add_user(&root, &new_user);
                pthread_mutex_lock(&screen);
                print_list(root, print_win);
                pthread_mutex_unlock(&screen);
            }
        }
    }
}