#include <stdio.h>
#include <stdlib.h>
#include "my_split.h"

void print_split(char** strings)
{
    int i = 0;
    while (strings[i] != NULL)
    {
        printf("'%s' ", strings[i]);
        i++;
    }
    printf("\n");
}

int main()
{
    print_split(my_split("A|B|C", "|"));           // {"A”, "B”, "C”, 0}
    print_split(my_split("A|B|C,D,E|F,G", "|,"));  // {"A”, "B”, "C”, "D”, "E”, "F”, "G”, 0}
    print_split(my_split("A,,C,D", ","));          // {"A”, "”, "C”, "D”, 0};
    print_split(my_split(",|", ",|"));             // {"”, "”, "”, 0};
    print_split(my_split(",|G'", ",|'"));
    return 0;
}