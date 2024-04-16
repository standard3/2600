#include <stdlib.h>
#include "my_rle.h"

#define MAX_SUCCESSIVE 9

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i += 1;
    return i;
}

char* rle_encode(const char* s)
{
    int   s_length  = my_strlen(s);
    char* container = malloc(sizeof(char) * (s_length * 2) + 1);

    int i, j;
    i = j = 0;

    while (i < s_length)
    {
        int occurrence = 1;

        while (s[i] == s[i + 1] && occurrence < MAX_SUCCESSIVE && (i + 1) < s_length) {
            occurrence++;
            i++;
        }

        container[j++] = occurrence + '0';
        container[j++] = s[i];

        i++;
    }

    container[j] = '\0';
    return container;
}

char* rle_decode(const char* s)
{
    int s_length = my_strlen(s);
    char *container = malloc(sizeof(char) * (s_length * MAX_SUCCESSIVE) + 1);

    int j = 0;
    for (int i = 0; i < s_length; i += 2)
    {
        int num = s[i] - '0';
        char ch = s[i + 1];

        for (int k = 0; k < num; k++)
            container[j++] = ch;
    }

    container[j] = '\0';
    return container;
}
