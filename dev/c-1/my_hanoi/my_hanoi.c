#include "stdio.h"
#include "stdlib.h"

void print_movement(int from, int to)
{
    putchar((char)from + '0');
    putchar('-');
    putchar('>');
    putchar((char)to + '0');
    putchar('\n');
}

void hanoi_recursion(unsigned n, int from, int aux, int to)
{
    if (n == 1) 
    {
        print_movement(from, to);
        return;
    }
    else
    {
        hanoi_recursion(n - 1, from, to, aux);
        print_movement(from, to);
        hanoi_recursion(n - 1, aux, from, to);
    }
}

extern void my_hanoi(unsigned n)
{
    hanoi_recursion(n, 1, 2, 3);
}