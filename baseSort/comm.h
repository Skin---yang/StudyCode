/*
 * this is common headfile for sort program
 *
 * */

#include <stdio.h>
#include <stdlib.h>

//not have reference in c
void swap(int *a, int *b)
{
    if(*a == *b)
        return;
    int temp = *a;
    *a = *b;
    *b = temp;
}
