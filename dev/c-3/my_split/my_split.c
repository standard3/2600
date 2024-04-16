#include <stdlib.h>
#include <stdio.h>
#include "my_split.h"

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i += 1;
    return i;
}

char* my_strdup(const char* str)
{
    char* out = (char*)malloc(sizeof(char) * (my_strlen(str) + 1));
    int i;
    for (i = 0; str[i] != 0; i++)
    {
            out[i] = str[i];
    }
    out[i + 1] = 0;
    return out;
}

char** my_split(const char* const str, const char* const sep)
{    
    int nb_seps = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        for (int j = 0; sep[j] != 0; j++)
        {
            if (str[i] == sep[j]) nb_seps++;
        }
    }

    char* str_copied = my_strdup(str);
    char **container = (char**)malloc(sizeof(char*) * (nb_seps + 2)); // 1 pour NULL, 1 pour sep + 1 mot

    int str_cur = 0;
    int pos = 0;

    for (int i = 0; str_copied[i] != 0; i++)
    {
        for (int j = 0; sep[j] != 0; j++)
        {
            if (str_copied[i] == sep[j])
            {
                str_copied[i] = 0;
                container[pos] = (str_copied + str_cur);
                
                str_cur = i + 1;
                pos += 1;
            }
        }
    }
    
    container[nb_seps] = (str_copied + str_cur);
    container[nb_seps + 1] = NULL;

    return container;
}
