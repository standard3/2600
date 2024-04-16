#include "my_get_nbr.h"

extern int my_get_nbr(char const str[])
{
    int result = 0;
    int sign = 1; // on considère le nombre positif

    // Vérifie le signe
    while (('-' == (*str)) || ((*str) == '+'))
    {
        if (*str == '-')
        sign = sign * -1;
        str++;
    }

    // Vérifier si dans [0-9]
    while ((*str >= '0') && (*str <= '9'))
    {
        result = (result * 10) + ((*str) - '0');
        str++;
    }

    return (result * sign);
}
