#include <stdio.h>
#include "my_strlen_recurs.h"

extern int my_strlen_recurs(char const str[])
{
    if (*str == '\0') return 0;
    
    return 1 + my_strlen_recurs(str + 1);  
}