#ifndef __HEXADECIMAL_NUMBER_H__
#define __HEXADECIMAL_NUMBER_H__

#include <stdio.h>

#define OK 0
#define ERROR 1

#define FIRST_BYTE 0xFFFFFF00
#define SECOND_BYTE 0xFFFF00FF
#define THIRD_BYTE 0xFF00FFFF
#define FOURTH_BYTE 0x00FFFFFF

int first_byte_change(int number, int byte, int *result);
int second_byte_change(int number, int byte, int *result);
int third_byte_change(int number, int byte, int *result);
int fourth_byte_change(int number, int byte, int *result);

#endif //__HEXADECIMAL_NUMBER_H__