#include <stdio.h>

#define N 11

int main() {
    int res = N * N, start = 1, up = 0, down = N - 1, left = 0, right = N - 1;
    int arr[N][N];
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         arr[i][j] = 0;
    //     }
    // }
    int i = 0, j = 0;
    while (start != res + 1) {
        if (i == up && j != right) {
            arr[i][j] = start;
            j++;
        } else if (i != down && j == right) {
            arr[i][j] = start;
            i++;
        } else if (i == down && j != left) {
            arr[i][j] = start;
            j--;
        } else if (i != up && j == left) {
            arr[i][j] = start;
            i--;
        } else
            arr[i][j] = start;
        if (i == down && j == left) up++;
        if (i == up && j == left && up > 0) right--;
        if (i == up && j == right && up > 0) down--;
        if (i == down && j == right && up > 0) left++;
        start++;
    }
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < N; m++) printf("%3d ", arr[n][m]);
        printf("\n");
    }
    return 0;
}