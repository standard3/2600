#include <stdio.h>

unsigned int my_strlen(const char s[]);

int main()
{
    char test[] = "123456789";

    printf("string : %s\nlength : %d", test, my_strlen(test));

    return 0;
}