#include <string.h>
#include "my_echo.h"
#include "my_putchar.h"

extern void my_echo(char const str[])
{
    for (int i = 0; i < strlen(str); i++)
        my_putchar(*(str + i));
}