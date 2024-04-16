#include "my_bitclean.h"

uint32_t my_bitclean(uint32_t __bitmap, int __pos)
{
    if (__pos >= 0)
        return __bitmap & ~(1 << __pos);

    else
        return __bitmap & ~(1 << ((sizeof(__pos) * 8) + (__pos - 1)));
}
