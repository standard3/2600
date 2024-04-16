#include <stdbool.h>
#include <stddef.h>
#include "my_get_nbr_base.h"

bool supported_char(const char c, const char *base)
{
    while (*base != '\0')
    {
        if (*base == c) return true;
        base++;
    }
    return false;
}

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i++;
    return i;
}

char* my_strchr(const char* str, int c)
{
    const char* position = NULL;

    for (int i = 0;; i++)
    {
        if (str[i] == c)
        {
            position = &str[i];
            break;
        }
        if (str[i] == '\0') break;
    }
    return (char *) position;
}

int my_get_nbr_base(const char num[], const char base[], const char sign)
{
    int result = 0;
    bool negative = false;

    if (*num == sign) { negative = true; num++; }

    while (*num != '\0')
    {
        if (!supported_char(*num, base)) return 0;

        result *= my_strlen(base);
        result += (int)(my_strchr(base, *num) - base);
        num++;
    }

    return (negative ? -result : result);
}