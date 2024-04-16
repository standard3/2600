#include <stdio.h>
#include "my_gen_str.h"

int main()
{
    printf("%s\n", my_gen_str("coucou", NULL));
    printf("%s\n", my_gen_str("coucou {0}", NULL));
    printf("%s\n", my_gen_str("coucou {1}", NULL));
    printf("%s\n", my_gen_str("coucou {999}", NULL));
    printf("%s\n", my_gen_str("coucou {0}", "test", NULL));
    printf("%s\n", my_gen_str("coucou {0} {0}", "test", NULL));
    printf("%s\n", my_gen_str("coucou {1} {0}", "test", "c'est", NULL));
    printf("%s\n", my_gen_str("coucou {{}} {1} {8} {oui} {0} { 0}", "0dd", "superH", NULL));
    
    return 0;
}