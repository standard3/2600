#include <stdio.h>
#include "my_nbr_digit_recurs.h"

extern int my_nbr_digit_recurs(int number, int base)
{
    if (number < base) return 1;
    if (base == 0) return -1;

    return 1 + my_nbr_digit_recurs(number / base, base);
}