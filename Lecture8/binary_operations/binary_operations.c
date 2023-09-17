#include "binary_operations.h"

int main() {
    int option = 0, first_num = 0, second_num = 0;
    int result = 0;
    while (option != 5) {
        printf("Choose option:\n1 - or\n2 - and\n3 - xor\n4 - negate\n5 - quit\nThen input two integer to make operation\n");
        scanf("%d", &option);
        if (option != 5) {
            scanf("%d %d", &first_num, &second_num);
        }
        switch(option) {
            case 1:
                or_function(first_num, second_num, &result);
                printf("first_num | second_num = %d\n", result);
                break;
            case 2:
                and_function(first_num, second_num, &result);
                printf("first_num & second_num = %d\n", result);
                break;
            case 3:
                xor_function(first_num, second_num, &result);
                printf("first_num ^ second_num = %d\n", result);
                break;
            case 4:
                negate_function(first_num, &result);
                printf("~first_num = %d\n", result);
                negate_function(second_num, &result);
                printf("~second_num = %d\n", result);
                break;
            case 5:
                break;
            default:
                printf("Incorrect option! Try again.\n");
                break;
        }
    }
    return 0;    
}