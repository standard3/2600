#include <stdarg.h>
#include <stdlib.h>
#include "my_gen_str.h"

int my_get_nbr_slice(char *const str, int start_pos, int end_pos)
{
    int number = 0;
    for (int i = start_pos; i <= end_pos; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            number = number * 10 + (str[i] - 48);
        else
            return -1;
    }

    return number;
}

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i += 1;
    return i;
}

char *my_gen_str(char *const __format, ...)
{
    size_t format_len = my_strlen(__format);

    char **placeholders = (char**)malloc(sizeof(char*) * (format_len + 1));

    va_list args_list;
    va_start(args_list, __format);
    char *next = va_arg(args_list, char *);

    size_t i = -1;
    size_t args_total_len = 0;

    // rempli le tableau des placeholders
    // + calcul longueur totale args
    while (next != NULL)
    {
        placeholders[++i] = next;
        args_total_len += my_strlen(next);
        next = va_arg(args_list, char *);
    }

    va_end(args_list);

    int args_num = ++i;

    char *result = (char*)malloc(format_len + args_total_len + 1);

    int result_offset = 0;
    size_t param_start_pos = format_len;
    int embedded_brackets = 0;

    for (i = 0; i < format_len; i++)
    {
        // début de placeholder
        if (__format[i] == '{')
        {
            if (param_start_pos != format_len)
                embedded_brackets++;
            else
                param_start_pos = i;
        }
        // fin de placeholder
        else if (__format[i] == '}')
        {
            if (embedded_brackets > 0)
                embedded_brackets--;
            else
            {
                // extraction du num du placeholder et 
                // remplace par l'arg correspondant
                int placeholder_index = my_get_nbr_slice(__format, param_start_pos + 1, i - 1);
                
                if (placeholder_index == -1)
                {
                    // si n'est pas un nombre, on le laisse
                    for (size_t j = param_start_pos; j <= i; j++)
                        result[result_offset++] = __format[j];
                }
                else if (placeholder_index < args_num)
                {
                    // si valide, on le remplace
                    char *placeholder_str = placeholders[placeholder_index];

                    while (*placeholder_str)
                        result[result_offset++] = *placeholder_str++;
                }

                param_start_pos = format_len; // actualisation position du placeholder
            }
        }
        // n'est pas un placeholder, on ajoute au résultat
        else if (i < param_start_pos)
            result[result_offset++] = __format[i];
    }

    result[result_offset] = '\0';

    return result;
}