#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> 
#include "my_load.h"

void my_printf(char*, ...);

int main()
{
    my_printf("num : %d\n", 123);
    my_printf("txt : %s\n", "okok");

    // Test load
    // int fd = open("test_load.ilist", O_RDONLY); 
    // if (fd < 0) return 1;

    // printf("===== test_load.ilist =====\n");
    // struct item_list* test = load_item_list(fd); 

    // print_item_list(test);

    // free(test);
    // close(fd);

    /* ----------------------------------------- */

    // Test write
    // int fd = open("test_save.ilist", O_RDONLY);
    // if (fd < 0) return 1;

    // printf("===== test_save.ilist =====\n");
    // struct item_list* test = load_item_list(fd);

    // save_item_list(fd, test);

    // free(test);
    // close(fd);

    return 0;
}