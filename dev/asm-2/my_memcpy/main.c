#include <stdio.h>

void* my_memcpy(void* dst, const void* src, unsigned int n);

int main()
{
    const int src = 10;
    int dest = 1;

    printf("avant memcpy = %d\n", dest);

    my_memcpy(&dest, &src, sizeof(int));
    printf("après memcpy = %d\n", dest);

    return 0;
}