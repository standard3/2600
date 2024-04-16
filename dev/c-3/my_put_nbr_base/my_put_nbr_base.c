#include <stdbool.h>
#include <stdlib.h>
#include "my_put_nbr_base.h"

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i++;
    return i;
}

char* my_put_nbr_base(int n, const char* base, char sign)
{
    // Set le signe
    bool negative = false;
    if (n < 0)
    {
        negative = true;
        n = -n;
    }

    // Calcul du nombre de nombres à retourner
    int n_dup = n, total_digits = 0;
    while (n_dup > 0)
    {
        n_dup /= my_strlen(base);
        total_digits++;
    }

    char* result = (char*)malloc(sizeof(char) * (total_digits + negative + 1));

    // Remplissage de la chaîne
    for (int i = total_digits + negative - 1; i >= negative; i--)
    {
        result[i] = base[n % my_strlen(base)];
        n /= my_strlen(base);
    }
    result[total_digits + negative] = '\0';
    
    // Ajouter le signe si nécessaire
    if (negative) result[0] = sign;

    return result;
}
