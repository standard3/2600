#include <stdio.h>

char* my_strdup(const char* s);

int main()
{
    char* test = "super test";
    char* newtest = my_strdup(test);

    printf("test = %s\nnewtest = %s\n", test, newtest);

    return 0;
}