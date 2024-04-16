#include "my_revstr.h"

extern void my_revstr(char str[])
{
    // Get char length
    int length = 0;
    while (str[length] != '\0') length++;

    // Reverse string
    for (int i = 0, j = length - 1; i < (length / 2); i++, j--)
    {
        char tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
    }
}
