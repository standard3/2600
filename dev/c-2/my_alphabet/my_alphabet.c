#include <unistd.h>
#include "my_alphabet.h"
#include <stdio.h>

extern int my_alphabet(void)
{
    for (int i = 'a'; i <= 'z'; i++)
    {
        char ch = (char)i;
        write(1, &ch, sizeof(char));
        if (i == 'z') return (i - 'a' + 1);
    }
}