#include <stdio.h>
#include <stdlib.h>

char* toBinary(int n, int len)
{
    char* binary = (char*)malloc(sizeof(char) * len);
    int k = 0;
    for (int i = (1 << (len - 1)); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}

int main()
{
    printf("value = %4d, pos = %3d, mask = %s, result = %d\n", 7,    2,   toBinary(~(1 << 2), 32),  my_bitclean(7,    2));
    printf("value = %4d, pos = %3d, mask = %s, result = %d\n", 103,  6,   toBinary(~(1 << 6), 32),  my_bitclean(103,  6));
    printf("value = %4d, pos = %3d, mask = %s, result = %d\n", 8542, -18, toBinary(~(1 << 32 - 18 + 1), 32), my_bitclean(8542, -18));

    return 0;
}