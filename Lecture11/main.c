#include <stdio.h>
#include <string.h>

struct People {
    char phone_number[13];
    char name[13];
    char surname[13];
    int id;
};

void start(struct People *list);

int main() {
    struct People list[100];
    start(list);
    for (int i = 0; i < 100; i++) {
        printf("%-3d %s %s %s\n", list[i].id, list[i].name, list[i].surname, list[i].phone_number);
    }
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