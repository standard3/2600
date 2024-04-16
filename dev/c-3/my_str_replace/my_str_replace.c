#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_str_replace.h"

// Dans une chaîne de caractère nouvellement alloué copie de la chaine ‘str’ dans laquelle
// chaque occurrence de ‘old_pat’ est remplacé par ‘new_pat’, tel que:

// Si ‘old_pat’ est NULL, ‘my_str_replace’ insérera ‘new_pat’ entre tous les caractères de
// str sans oublier avant le premier caractère et après le dernier.
// Si ‘new_pat’ est NULL, chaque occurrence de ‘old_pat’ sera supprimé de la nouvelle chaîne.
// Si ‘str’ est NULL, ‘my_str_replace’ retourne NULL.

char *my_str_replace(const char *old_pat, const char *str, const char *new_pat)
{
    if (str == NULL) return NULL;

    int old_pat_len = (old_pat != NULL) ? strlen(old_pat) : 0;
    int new_pat_len = (new_pat != NULL) ? strlen(new_pat) : 0;
    int str_len = strlen(str);

    // Compter le nombre d'occurrences de old_pat dans str
    int count = 0;
    if (old_pat_len > 0)
    {
        const char *tmp = str;
        while ((tmp = strstr(tmp, old_pat)))
        {
            count++;
            tmp += old_pat_len;
        }
    }
    // old_pat est NULL => on insère new_pat entre chaque caractère
    else count = str_len;

    // Réserve la chaine out en fonction de new_pat_len
    int out_len = str_len + count * ((new_pat_len > 0) ? new_pat_len : -old_pat_len);
    char *out = (char*)malloc(sizeof(char) * (out_len) + 1);

    const char *str_ptr = str;
    char *out_ptr = out;

    if (old_pat == NULL)
    {
        // Insérer new_pat entre tous les caractères de str
        while (*str_ptr)
        {
            if (new_pat_len > 0)
            {
                strncpy(out_ptr, new_pat, new_pat_len);
                out_ptr += new_pat_len;
            }

            *out_ptr = *str_ptr;
            out_ptr++;
            str_ptr++;
        }
    }
    else
    {
        while (*str_ptr)
        {
            // Remplace les occurrences de old_pat par new_pat 
            if (strncmp(str_ptr, old_pat, old_pat_len) == 0)
            {
                if (new_pat_len > 0)
                {
                    strncpy(out_ptr, new_pat, new_pat_len);
                    out_ptr += new_pat_len;
                }
                str_ptr += old_pat_len;
            }
            // Supprime old_pat
            else
            {
                *out_ptr = *str_ptr;
                out_ptr++;
                str_ptr++;
            }
        }
    }
    *out_ptr = '\0';

    return out;
}
