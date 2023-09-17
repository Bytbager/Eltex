#ifndef __BINARY_OPERATIONS_H__
#define __BINARY_OPERATIONS_H__

#include <stdio.h>

#define OK 0

int and_function(int first, int second, int *res);
int negate_function(int number, int *res);
int or_function(int first, int second, int *res);
int xor_function(int first, int second, int *res);

#endif //__BINARY_OPERATIONS_H__