#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>
#include "my_load.h"

size_t my_strlen(const char* str);

#include <stdarg.h>    
#include <unistd.h>
#include <stdbool.h>
void my_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

void my_puts(char const str[])
{
    for (size_t i = 0; i < my_strlen(str); i++)
        my_putchar(*(str + i));
}

char* my_nbr_base_to_str(int num, uint32_t base)
{
    char  buffer[50]; 
    char* rep = "0123456789ABCDEF";
    char* pBuffer = NULL; 

    pBuffer = &buffer[49]; // oui on mélange la convention microsoft à linux
    *pBuffer = '\0';

    do
    { 
        *--pBuffer = rep[num % base]; 
        num /= base; 
    } while(num != 0); 

    return(pBuffer); 
}

#include <stdio.h>
void my_printf(char* format, ...)
{
    va_list args_list;
    va_start(args_list, format);

    while (*format != '\0')
    {
        // aucun format spécifié
        while (*format != '%')
        {
            if( *format == '\0') return;
            my_putchar(*format);
            format++;
        }

        format++; // on prend le caractère format
        switch (*format)
        {
        // format string
        case 's':
            my_puts(va_arg(args_list, char*));
            break;
        
        // format entier
        case 'd':
            my_puts(my_nbr_base_to_str(va_arg(args_list, int), 10)); // fixme: ça fonctionne pas
            break;

        default:
            // erreur format pas supporté
            break;
        }
        format++;
    }
}

void test()
{
    printf("sizeof(enum item_type)    = %ld bytes\n", sizeof(enum item_type));
    printf("sizeof(struct item_staff) = %ld bytes\n", sizeof(struct item_staff));
    printf("sizeof(struct item_stuff) = %ld bytes\n", sizeof(struct item_stuff));
    printf("sizeof(union item_union)  = %ld bytes\n", sizeof(union item_union));
    printf("sizeof(struct item)       = %ld bytes\n", sizeof(struct item));
    printf("sizeof(struct item_list)  = %ld bytes\n", sizeof(struct item_list));
    printf("sizeof(struct tm)         = %ld bytes\n", sizeof(struct tm));
    printf("------------------------------------\n");
    printf("alignof(enum item_type)    = %lu bytes\n", alignof(enum item_type));
    printf("alignof(struct item_staff) = %lu bytes\n", alignof(struct item_staff)); 
    printf("alignof(struct item_stuff) = %lu bytes\n", alignof(struct item_stuff)); 
    printf("alignof(union item_union)  = %lu bytes\n", alignof(union item_union)); 
    printf("alignof(struct item)       = %lu bytes\n", alignof(struct item)); 
    printf("alignof(struct item_list)  = %lu bytes\n", alignof(struct item_list)); 
    printf("------------------------------------\n");
    printf("char        = %lu bytes\n", alignof(char));
    printf("short       = %lu bytes\n", alignof(short)); 
    printf("int         = %lu bytes\n", alignof(int)); 
    printf("long        = %lu bytes\n", alignof(long)); 
    printf("long long   = %lu bytes\n", alignof(long long)); 
    printf("float       = %lu bytes\n", alignof(float)); 
    printf("double      = %lu bytes\n", alignof(double)); 
    printf("long double = %lu bytes\n", alignof(long double));

    return;
}