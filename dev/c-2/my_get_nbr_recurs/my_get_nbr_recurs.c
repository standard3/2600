#include "my_get_nbr_recurs.h"

int my_get_nbr_recurs_worker(char const str[], int sign, int result, int index)
{
    if (str[index] == '\0') return result * sign;

    // Vérifie le signe
    if (str[index] == '-')
    {
        sign *= -1;
    } 
    else if (str[index] != '+') 
    {
        // Vérifie sur dans [0-9]
        if (str[index] >= '0' && str[index] <= '9')
        {
            result = (result * 10) + (str[index] - '0');
        }
        else
        {
            return (result * sign);
        }
    }

    return my_get_nbr_recurs_worker(str, sign, result, index + 1);
}

int my_get_nbr_recurs(char const str[])
{
    return my_get_nbr_recurs_worker(str, 1, 0, 0);
}
