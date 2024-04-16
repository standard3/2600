#include <stdio.h>

char* my_strrev(const char* s);

int main()
{
    const char test[] = "abcdefgh";
    printf("%s\n", test);
    char* test2 = my_strrev(test);
    printf("%s\n", test);
    printf("test : %p\n", (void*)test);
    printf("test2 : %p\n", (void*)test2);

    return 0;
}