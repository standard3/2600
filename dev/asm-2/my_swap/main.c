#include <stdio.h>

void my_swap(long int* nbr1, long int* nbr2);

int main()
{
    long a = 1;
    long b = 2;

    printf("Before swap:\na = %d\nb = %d\n", a, b);
    my_swap(&a, &b);
    printf("After swap:\na = %d\nb = %d\n", a, b);

    return 0;
}