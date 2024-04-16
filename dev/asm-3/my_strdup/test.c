#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main()
{
    printf("%d\n", MAP_PRIVATE|MAP_ANONYMOUS);

    return 0;
}