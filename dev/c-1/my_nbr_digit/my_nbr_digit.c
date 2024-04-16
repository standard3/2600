#include <stdio.h>
#include "my_nbr_digit.h"

extern int my_nbr_digit(int number, int base)
{
    int count = 0;

    if (base == 0) return -1;
    if (number == 0) return 1;

    while (number > 0)
    {
        number /= base;
        count++;
    }

    return count;
}
