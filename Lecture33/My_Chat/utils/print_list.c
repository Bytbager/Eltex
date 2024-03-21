#include "../my_chat.h"

int print_list(struct user_list *root, WINDOW *win) {
    struct user_list *tmp = root;
    
    wclear(win);
    wrefresh(win);
    while(tmp != NULL) {
        wprintw(win, "%s\n", tmp->user.nickname);
        tmp = tmp->next;
    }
    wrefresh(win);
    return 0;
}