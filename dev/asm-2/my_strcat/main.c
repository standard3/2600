#include "stdio.h"

char* my_strcat(char *dst, const char *src);

int main()
{
    char buffer[100] = "Hello ";

    printf("avant cat : %s\n", buffer);
    my_strcat(buffer, "world");
    my_strcat(buffer, "!");
    printf("après cat : %s\n", buffer);

    return 0;
}