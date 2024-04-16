#include <stdio.h>
#include "my_get_nbr_base.h"

int main() 
{
    const char num1[] = "%123";
    const char base1[] = "0123456789";
    const char sign1 = '%';

    const char num2[] = "^dab";
    const char base2[] = "xabcdefg";
    const char sign2 = '^';

    int result1 = my_get_nbr_base(num1, base1, sign1);
    int result2 = my_get_nbr_base(num2, base2, sign2);

    printf("num = %s; base = %s; sign = %c\nresult = %d\n", num1, base1, sign1, my_get_nbr_base(num1, base1, sign1));
    printf("num = %s; base = %s; sign = %c\nresult = %d\n", num2, base2, sign2, my_get_nbr_base(num2, base2, sign2));

    return 0;
}