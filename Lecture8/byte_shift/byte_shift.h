#ifndef __BYTE_SHIFT_H__
#define __BYTE_SHIFT_H__

#include <stdio.h>

#define OK 0
#define ERROR 1

int right_shift(int number, int bits, int *result);
int left_shift(int number, int bits, int *result);

#endif //__BYTE_SHIFT_H__