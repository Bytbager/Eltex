#include <stdio.h>
#include <string.h>

struct People {
    int id;
    char phone_number[20];
    char name[20];
    char surname[20];
};

void start(struct People *list);
void menu(struct People *list);
void add_sub(struct People *list);
void del_sub(struct People *list);
void show_subs(struct People *list);

int main() {
    struct People list[100];
    start(list);
    menu(list);
    return 0;
}

void start(struct People *list) {
    for (int i = 0; i < 100; i++) {
        list[i].id = i + 1;
        strcpy(list[i].name, "0");
        strcpy(list[i].surname, "0");
        strcpy(list[i].phone_number, "0");
    }
}

void menu(struct People *list) {
    int button = 0;
    while(button != 9) {
        printf("\n\nПоказать существующих абонентов - 1\nНовый абонент - 2\nУдалить абонента - 3\nВыход из программы - 9\n\n");
        scanf("%d", &button);
        switch(button) {
            case 1: show_subs(list); break;
            case 2: add_sub(list); break;
            case 3: del_sub(list); break;
            case 9: return;
            default: printf("\n\nНеизвестная команда, попробуйте снова.\n\n"); break;
        }
    }
}

void show_subs(struct People *list) {
    for (int i = 0; i < 100; i++) {
        if (strcmp(list[i].name, "0") != 0 || strcmp(list[i].surname, "0") != 0 || strcmp(list[i].phone_number, "0") != 0) {
            printf("%-3d %s %s %s\n", list[i].id, list[i].surname, list[i].name, list[i].phone_number);
        }
    }
}

void add_sub(struct People *list) {
    for (int i = 0; i < 100; i++) {
        if (strcmp(list[i].name, "0") == 0 && strcmp(list[i].surname, "0") == 0 && strcmp(list[i].phone_number, "0") == 0) {
            printf("\n\nВведите фамилию абонента (максимум 19 символов):\n\n");
            scanf("%s",list[i].surname);
            printf("\n\nВведите имя абонента (максимум 19 символов):\n\n");
            scanf("%s",list[i].name);
            printf("\n\nВедите номер тел. абонента (максимум 19 символов):\n\n");
            scanf("%s",list[i].phone_number);
            printf("\n\nАбонент добавлен.\n\n");
            return;
        }
    }
}

void del_sub(struct People *list) {
    char buffer[13];
    printf("\n\nВведите номер абонента (максимум 19 символов):\n\n");
    scanf("%s",buffer);
    for (int i = 0; i < 100; i++) {
        if (strcmp(buffer, list[i].phone_number) == 0) {
        strcpy(list[i].name, "0");
        strcpy(list[i].surname, "0");
        strcpy(list[i].phone_number, "0");
        printf("\n\nАбонент удален.\n\n");
        return;            
        }
    }
    printf("\n\nАбонент с таким номером не найден. Возврат в меню.\n\n");
    return;
}