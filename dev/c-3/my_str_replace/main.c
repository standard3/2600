#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_str_replace.h"

void check(const char *o, const char *s, const char *n, const char *cmp)
{
    char *res = my_str_replace(o, s, n);

    if (!strcmp(res, cmp))
        printf("OK %s\n", res);

    free(res);
}

int main(void)
{
    check("o",      "bobo", "",     "bb");
    check("o",      "bobo", "i",    "bibi");
    check("o",      "bobo", "oo",   "booboo");
    check(NULL,       "bobo", "a",    "bobo");
    check("bo",     "bobo", "k",    "kk");
    check("bo",     "bobo", "be",   "bebe");
    check("bobo",   "bobo", "bubu", "bubu");
    check("bobobo", "bobo", "bubu", "bobo");
    
    return 0;
}