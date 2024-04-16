#include <stdio.h>
#include <string.h>

void my_countv(char s[], int size, int v[6]);

int main()
{
    char test[] = "abcdefghihklmnopqrstuvwxyz";
    int vowels[6] = { 0 }; 

    my_countv(test, strlen(test), vowels);

    printf("string : %s\n", test);
    for (int i = 0; i < 6; i++)
        printf("vowels[%d] = %d\n", i, vowels[i]);

    return 0;
}