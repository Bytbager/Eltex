#include "../my_chat.h"

int delete_user(struct user_list **root, struct User **exited_user) {
    struct user_list *tmp = *root, *exited_tmp;
    
    if (tmp->next == NULL) {
        memset(tmp, 0, sizeof(struct user_list));
        (*root)->next = NULL;
        return 0;
    } else if (tmp->user.pid == (*exited_user)->pid) {
        exited_tmp = tmp;
        *root = tmp->next;
        free(exited_tmp);
        return 0;
    }

    while(tmp != NULL) {
        if (tmp->next->user.pid == (*exited_user)->pid) {
            exited_tmp = tmp->next;
            tmp->next = tmp->next->next;
            free(exited_tmp);
            return 0;
        }
        tmp = tmp->next;
    }
}