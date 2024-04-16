#include <stdio.h>

int my_mul_arrays(int a[4], int b[4]);

int main()
{
    int a[] = {1, 2, 3, 4};
    int b[] = {1, 2, 3, 4};

    printf("total = %d", my_mul_arrays(a, b));

    return 0;
}