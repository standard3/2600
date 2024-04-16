#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_eratosthenes.h"

// Voir https://fr.wikipedia.org/wiki/Crible_d%27%C3%89ratosth%C3%A8ne

extern void my_eratosthenes(int n)
{
    if (n > 1000) return;

    bool *limit = (bool*)malloc(sizeof(bool) * n);

    // On rempli de nombres naturels impairs
    for (int i = 2; i < n; i++)
        limit[i] = true;

    // Crible d'Eratosthenes
    for (int i = 2; i < n; i++)
        if (limit[i])
            for (int j = i; (i * j) < n; j++)
                limit[i * j] = false;

    // Affichage
    for (int i = 0; i < n + 1; i++)
        if (limit[i]) 
            printf("%d\n", i);
}
