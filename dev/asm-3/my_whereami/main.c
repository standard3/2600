#include <stdio.h>
#include <stdint.h>

int64_t my_whereami(int64_t* where);

int main()
{
    int64_t where;
    int64_t size = my_whereami(&where);

    printf("my_wherami() => %p (%d bytes)\n", (void*)where, size);
    
    return 0;
}
