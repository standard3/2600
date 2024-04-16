// gcc -f-no-stack-protector -g ...

#include <stdio.h>

int fint(int a, int b, int c, int d, int e, int f, int g, int h)
{
    char tab[10];
    //...
}

double fdouble(double a, double b, double c, double d) { }

int main()
{
    fint(1, 2, 3, 4, 5, 6, 7, 8);
    fdouble(1.2, 3.4, 5.6, 7.8);
};