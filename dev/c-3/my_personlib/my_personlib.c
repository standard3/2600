#define _XOPEN_SOURCE
#include <stdlib.h>
#include "my_personlib.h"

char* my_strncpy(char* dest, const char* src, size_t n)
{
    if (dest == NULL)
        return NULL;

    char* p_dest = dest;

    while (*src && n--)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return p_dest;
}

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i += 1;
    return i;
}

#include <stdio.h>
int my_strcmp(char* first, char* second)
{
    if (my_strlen(first) != my_strlen(second))
        return 1;

    int index = 0;
    while (first[index] != '\0')
    {
        if (first[index] != second[index])
            return 1;
        index++;
    }

    return 0;
}

// construit la base de la liste chaîné
struct staff *new_staff()
{
    struct staff* tmp = malloc(sizeof(struct staff));
    tmp->first = NULL;
    tmp->last  = NULL;

    return tmp;
}

// libère tous les élément de la liste
void destroy_staff(struct staff *staff)
{
    struct member* current = staff->first;
    struct member* next;
    
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(staff);
}   

// ajoute un élément a la fin de la liste de staff, et retourne
void staff_append_member(struct staff *staff, struct member *person)
{
    if (staff->first == NULL)
    {
        staff->first = person;
        staff->last = person;
    }
    else
    {
        // Modifie le champ next du last member
        struct member* last = staff->last;
        last->next = person;

        // Modifie le champ last du staff
        staff->last = person;
    }
}

// ajoute un élément au debut de la liste de staff
void staff_prepend_member(struct staff *staff, struct member *person)
{
    if (staff->first == NULL)
    {
        staff->first = person;
        staff->last = person;
    }
    else
    {
        // Modifie le champ prev du first member
        struct member* first = staff->first;
        first->prev = person;

        // Modifier le champ first du staff
        staff->first = person;
    }    
}

// insert un élément apres le membre nommer name
void staff_insert_after_member_name(struct staff *staff, char *name, struct member *person)
{
    if (staff->first == NULL || staff->last == NULL)
        return; // Pas de membre

    struct member* current = staff->first;

    while (my_strcmp(current->name, name) == 0)
        current = current->next;

    if (current == NULL) return; // Nom pas trouvé

    // Si insert after last, définir celui-ci comme nouveau last
    // Et pas de next
    if (staff->last == current)
    {
        staff->last = person;
        person->next = NULL;
    }

    // Modifie le champ prev du next de current
    person->prev = current;

    // Modifie le champ next de current
    current->next = person;
}

// construit un nouveau membre
struct member *new_member(const char *name, const char *lastname, const char *birthdate)
{
    struct member* tmp = malloc(sizeof(struct member));

    my_strncpy(tmp->name,     name,     20);
    my_strncpy(tmp->lastname, lastname, 40);

    struct tm dob;

    if (*(strptime(birthdate, "%Y-%m-%d", &dob)) == '\0')
    {
        tmp->birth = dob;
    }
    // todo: gérer le comportement où le parsing se fait mal
    return tmp;
}