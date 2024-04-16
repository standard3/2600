#include <stdio.h>
#include "my_strlen.h"

extern int my_strlen(char const str[])
{
    int count = 0;
    do
    {
        if (*(str + count) == '\0')
            return count;
        count++;
    } while (1);
}