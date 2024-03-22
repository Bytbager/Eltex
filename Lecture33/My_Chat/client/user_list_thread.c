#include "../my_chat.h"

pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;

void user_list_thread(int *read_pipe) {
    WINDOW *main_win, *print_win;    
    struct User *new_user = NULL;
    struct user_list *root = NULL, *tmp = NULL;
    char buff[256];
    
    pthread_mutex_lock(&screen);
    new_user = calloc(1, sizeof(struct User));
    if (new_user == NULL)
        errExit("new_user calloc error!\n");

    root = calloc(1, sizeof(struct user_list));
    if (root == NULL)
        errExit("root calloc error!\n");
    pthread_mutex_unlock(&screen);

    tmp = root;

    int x, y;
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

    while (1) {
        memset(new_user, 0, sizeof(struct User));
        rc = read(*read_pipe, new_user, sizeof(struct User));
        if ( rc == -1)
            errExit("user_list read error!\n");
        else if (rc > 0) {
            if (new_user->mqds == DELETED_USER) {
                delete_user(&root, &new_user);
                pthread_mutex_lock(&screen);
                print_list(root, print_win);
                pthread_mutex_unlock(&screen);
            } else if (new_user->mqds == SERVER_RECEIVED_DELETION_REQUEST) {
                pthread_mutex_lock(&screen);
                delwin(print_win);
                delwin(main_win);
                free(new_user);
                if (root != NULL)
                free(root);
                pthread_mutex_unlock(&screen);
                pthread_exit(NULL);
            } else {
                add_user(&root, &new_user);
                pthread_mutex_lock(&screen);
                print_list(root, print_win);
                pthread_mutex_unlock(&screen);
            }
        }
    }
}