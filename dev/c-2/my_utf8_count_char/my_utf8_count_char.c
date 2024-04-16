#include "my_utf8_count_char.h"

extern int my_utf8_count_char(const char *str)
{
    int count = 0;
    while (*str)
    {
        // > UTF-8 encodes code points in one to four bytes, depending on the value of the code point.
        // Les octets supplémentaires commencent toujours avec les bits '10...'
        // Le premier ne commence jamais avec cette séquence, il suffit 
        // d'exclure ceux qui matchent cette condition

        // (*str++ & 0xC0) => on conserve les 2 bits les plus significatifs 
        //  -> 0xC0 = 0b11000000

        // != 0x80 => on vérifie que le char ne commence pas par 10
        // -> 0x80 = 0b10000000

        if ((*str++ & 0xC0) != 0x80)
            count++;
    }
    return count;
}