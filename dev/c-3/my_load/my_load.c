#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "my_load.h"

#define FILE_FORMAT "ItemList v1.0"

size_t my_strlen(const char* str)
{
    int i = 0;
    while (str[i] != 0) i += 1;
    return i;
}

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

uint32_t item_list_size(struct item_list* list)
{
    uint32_t size = 0;
    struct item_list* tmp = list;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        size++;
    }
    free(tmp);

    return size;
}

// créer un nouvel Item
struct item* new_item(enum item_type type, union item_union* data)
{
    // créer nouvel item dynamiquement
    struct item* new = malloc(sizeof(struct item_list));
    
    // définir son type et les données de l'union
    new->type = type;
    new->udata = *data;

    return new;
}

// ajoute un Item à la liste
struct item_list* append_item_list(struct item_list* list, struct item* item)
{
    // faire boucle pour récupérer le dernier item_list 
    // => jusqu'à ce que item_list->next == NULL
    struct item_list* last = list;

    while (last->next != NULL)
        last = last->next;

    // créer un nouvel item_list dynamiquement
    struct item_list* new = malloc(sizeof(struct item_list));

    // y ajouter l'item + init le next à NULL
    new->data = item;
    new->next = NULL;

    // si premier élément, modifier cet élément
    // sinon modifier le last->next par le nouvel item_list
    if (last->data == NULL) 
        *last = *new;
    else
        last->next = new;

    return new;
}

// temp stdio
#include <stdio.h>
// Affiche un Item
void print_item(struct item* item)
{
    // todo: écrire fonction my_printf avec write
    // s'inspirer de my_gen_str et my_cat

    if (item->type == STAFF)
    {
        const size_t MAX_SIZE = 10 + 1; // = YYYY-MM-DD (ISO-8601)

        char birth[MAX_SIZE];
        char begin_job[MAX_SIZE];

        strftime(birth,     MAX_SIZE, "%Y-%m-%d", &item->udata.staff.birth);
        strftime(begin_job, MAX_SIZE, "%Y-%m-%d", &item->udata.staff.begin_job);

        printf("ITEM TYPE: STAFF\n");
        printf("name:      %s\n", item->udata.staff.name);
        printf("lastname:  %s\n", item->udata.staff.lastname);
        printf("birth:     %s\n", birth);
        printf("begin_job: %s\n", begin_job);
    }
    else
    {
        printf("ITEM TYPE: STUFF\n");
        printf("id:     %d\n", item->udata.stuff.id);
        printf("title:  %s\n", item->udata.stuff.title);
        printf("desc:   %s\n", item->udata.stuff.desc);
        printf("height: %f\n", item->udata.stuff.height);
        printf("width:  %f\n", item->udata.stuff.width);
        printf("depth:  %f\n", item->udata.stuff.depth);
        printf("weight: %f\n", item->udata.stuff.weight);
    }
}

void print_item_list(struct item_list* list)
{
    struct item_list* last = list;
    
    while (last->next != NULL)
    {
        print_item(last->data); printf("\n");
        last = last->next; // occurence suivante
    }
}

// Ecrire ou lire à partir d'un fichier ouvert dont on possède le File Descriptor
void save_item_list(int fd, struct item_list* list)
{
    // Ecrit le Magic Byte
    char file_format[] = FILE_FORMAT;
    ssize_t nb_bytes_wrote = write(fd, file_format, my_strlen(file_format));

    if (nb_bytes_wrote <= 0)
        return; // on ne peut pas retourner d'erreur D:

    // Ecrit le nombre d'objets
    int32_t total_objects = item_list_size(list);

    nb_bytes_wrote = write(fd, &total_objects, sizeof(int32_t));

    if (nb_bytes_wrote <= 0)
        return;

    // Boucle sur le nombre d'objets
    struct item_list* next_list = list;
    
    do
    {
        if (nb_bytes_wrote == -1) return;

        enum item_type type = next_list->data->type;

        if (type == STAFF)
        {
            nb_bytes_wrote = write(
                fd,
                &next_list->data->udata.staff, 
                sizeof(struct item_staff)
            );
        }
        else if (type == STUFF)
        {
            nb_bytes_wrote = write(
                fd, 
                &next_list->data->udata.stuff,
                sizeof(struct item_stuff)
            );
        }

        next_list = next_list->next;
    } while (next_list->next != NULL);
    
    return;
}

struct item_list* load_item_list(int fd)
{
    // Créer nouvelle item_list
    struct item_list* container = malloc(sizeof(struct item_list));

    // Lit le magic byte et vérifie le bon format
    char file_format[20] = "";
    ssize_t format_bytes_read = read(fd, file_format, sizeof(char) * 20);

    if (format_bytes_read == 0)
        return NULL;

    if (my_strcmp(file_format, FILE_FORMAT) != 0)
        return NULL;

    // Lire nombre d'objets
    int32_t total_objects;
    ssize_t objects_bytes_read = read(fd, &total_objects, sizeof(int32_t));

    if (objects_bytes_read == 0)
        return NULL;

    ssize_t nb_bytes_read = 0;

    int index = 0;

    enum item_type type;

    // Boucle sur le nombre d'objets
    do
    {
        if (index > total_objects) break;

        struct item* new_item = malloc(sizeof(struct item));
        new_item->type = type;

        // todo: trouver un moyen de retrécir ce code
        if (type == STAFF)
        {
            // Lit la structure
            nb_bytes_read = read(
                fd,
                &new_item->udata.staff,
                sizeof(struct item_staff)
            );

            // L'ajoute à l'item_list
            append_item_list(container, new_item);
            index++;
            //print_item(new_item); printf("\n");
        }
        else if (type == STUFF)
        {
            nb_bytes_read = read(
                fd,
                &new_item->udata.stuff,
                sizeof(struct item_stuff)
            );
            
            append_item_list(container, new_item);
            index++;
            //print_item(new_item); printf("\n");
        }

    } while ((nb_bytes_read = read(fd, &type, sizeof(enum item_type))) > 0); // Récupére l'item_type

    return container;
}