#include "hexadecimal_number.h"

int main() {
    int option = 0;
    int number = 0;
    int byte = 0;
    int result = 0;
    while (option != 5) {
        printf("Choose byte you want to change:\n1 - first\n2 - second\n3 - third\n4 - fourth\n5 - quit\n");
        scanf("%d", &option);
        if (option == 1 || option == 2 || option == 3 || option == 4) {
            printf("Choose hexadecimal number you want to change:\n");
            scanf("%x", &number);
            printf("Type byte value:\n");
            scanf("%x", &byte);
        }
        switch(option) {
            case 1:
                first_byte_change(number, byte, &result);
                printf("result = %x\n", result);
                break;
            case 2:
                second_byte_change(number, byte, &result);
                printf("result = %x\n", result);
                break;
            case 3:
                third_byte_change(number, byte, &result);
                printf("result = %x\n", result);
                break;
            case 4:
                fourth_byte_change(number, byte, &result);
                printf("result = %x\n", result);
                break;
            case 5:
                break;
            default:
                printf("Incorrect option! Try again!\n");
                break;
        }
    }
    return 0;
}