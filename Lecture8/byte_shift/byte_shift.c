#include "byte_shift.h"

int main() {
    int option = 0;
    int number = 0;
    int bits = 0;
    int result = 0;
    while (option != 3) {
        printf("Choose option:\n1 - right shift\n2 - left shift\n3 - quit\n");
        scanf("%d", &option);
        if (option == 1 || option == 2) {
            printf("Now choose int number and amount of bits to shift.\n");
            scanf("%d %d", &number, &bits);
        }
        switch (option) {
            case 1:
                right_shift(number, bits, &result);
                printf("%d >> %d = %d\n", number, bits, result);
                break;
            case 2:
                left_shift(number, bits, &result);
                printf("%d << %d = %d\n", number, bits, result);
                break;
            case 3:
                break;
            default:
                printf("Incorrect option! Try again!\n");
                break;
        }
    }
    return 0;
}