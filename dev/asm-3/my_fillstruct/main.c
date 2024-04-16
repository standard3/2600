#include <stdint.h>
#include <stdio.h>

struct _my_struct { int64_t i; double d; };

void my_fillstruct(struct _my_struct*, int64_t, double);

int main()
{
    struct _my_struct* test;
    my_fillstruct(test, 1, 3.14);

    printf("int = %d\ndouble = %lf\n", test->i, test->d);

    return 0;
}