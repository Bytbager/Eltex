#include "../my_chat.h"

int add_user(struct user_list **root, struct User **new_user) {
    struct user_list *tmp = *root;

    if ((*root)->user.pid != 0) {
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = calloc(1, sizeof(struct user_list));
        if (tmp->next == NULL)
            errExit("tmp->next calloc error!\n");
        tmp = tmp->next;
    }

    tmp->user.pid = (*new_user)->pid;
    strncat(tmp->user.nickname, (*new_user)->nickname, 16);
        
    tmp->next = NULL;
    return 0;
}