#include <stdio.h>
#include "my_put_nbr_base.h"

int main()
{
    printf("%s\n", my_put_nbr_base(12,    "0123456789",       '-'));
    printf("%s\n", my_put_nbr_base(12,    "01234567",         '-'));
    printf("%s\n", my_put_nbr_base(100,   "0123456789ABCDEF", '-'));
    printf("%s\n", my_put_nbr_base(-100,  "0123456789ABCDEF", '-'));
    printf("%s\n", my_put_nbr_base(-1217, "TRICHE",           'P'));

    // Pas de free :>

    return 0;
}