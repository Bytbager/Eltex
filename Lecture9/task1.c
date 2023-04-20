#include <stdio.h>

#define N 3

int main() {
    int res = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++, res++) printf("%3d ", res);
        printf("\n");
    }
    return 0;
}