#include "subscriber_list.h"

int main() {
    struct People *list = NULL;
    int subscriber_count = 0;
    int option = 0;
    int err = OK;
    while(option != 4) {
        printf("Choose option:\n1 - add new subscriber.\n"
                "2 - delete subscriber.\n3 - show subscriber"
                "list.\n4 - quit.\n");
        scanf("%d", &option);
        switch(option) {
            case 1:
                if (subscriber_count > 0) {
                    list = realloc(list, (subscriber_count + 1) * sizeof(struct People));
                    if (list == NULL) {
                        perror("List didn't get memory!\n");
                        err = ERROR;
                        quit_program(&subscriber_count, list, err);
                    }
                } else if (subscriber_count == 0) {
                    list = malloc(sizeof(struct People));
                    if (list == NULL) {
                        perror("List didn't get memory!\n");
                        err = ERROR;
                        quit_program(&subscriber_count, list, err);
                    }
                }
                new_subscriber(&subscriber_count, list);
                break;
            case 2:
                delete_subscriber(&subscriber_count, list);
                list = realloc(list, subscriber_count * sizeof(struct People));
                if (list == NULL && subscriber_count > 0) {
                    perror("List didn't get memory!\n");
                    err = ERROR;
                    quit_program(&subscriber_count, list, err);
                }
                break;
            case 3:
                show_subscriber_list(&subscriber_count, list);
                break;
            case 4:
                quit_program(&subscriber_count, list, err);
                break;
            default:
                printf("Incorrect option! Try again!\n");
                break;
        }
    }
    return 0;
}