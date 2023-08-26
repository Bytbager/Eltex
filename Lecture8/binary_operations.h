#ifndef __BINARY_OPERATIONS_H__
#define __BINARY_OPERATIONS_H__

#define OK 0
#define ERROR 1

int and_function(int first, int second, int *res);
int or_function(int first, int second, int *res);
int xor_function(int first, int second, int *res);
int negate_function(int *res);

#endif //__BINARY_OPERATIONS_H__