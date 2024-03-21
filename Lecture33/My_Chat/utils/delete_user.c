#include "../my_chat.h"

int delete_user(struct user_list **root, struct User **exited_user) {
    struct user_list *tmp = *root, *exited_tmp;
    while(tmp != NULL) {
        if (tmp->next->user.pid == (*exited_user)->pid) {
            exited_tmp = tmp->next;
            tmp->next = tmp->next->next;
            free(exited_tmp);
            break;
        }
        tmp = tmp->next;
    }
    return 0;
}