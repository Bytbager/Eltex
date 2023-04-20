#include <stdio.h>

#define N 25

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i + j >= N - 1)
                printf("%d ", 1);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
    return 0;
}