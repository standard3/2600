#include <stdio.h>

long int my_factorial(long int n);

int main()
{
    int n = 2;

    printf("%d! = %ld\n", n, my_factorial(n));
    puts("doit valoir 120\n");

    return 0;
}