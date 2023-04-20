#include <stdio.h>

#define N 3

int main() {
    int arr[N];
    int res = 1, startpoint = 0, endpoint = N - 1, tmp = 0;
    for (int i = 0; i < N; i++, res++) arr[i] = res;
    while (endpoint != N / 2 - 1) {
        tmp = arr[startpoint];
        arr[startpoint] = arr[endpoint];
        arr[endpoint] = tmp;
        startpoint++;
        endpoint--;
    }
    for (int i = 0; i < N; i++) {
        if (i != N - 1)
            printf("%d ", arr[i]);
        else
            printf("%d", arr[i]);
    }
    return 0;
}