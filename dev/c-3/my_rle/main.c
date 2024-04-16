#include <stdio.h>
#include "my_rle.h"

int main()
{               // 9A1A1C4B
    char* test = "AAAAAAAAAACBBBB"; // A1B2C3D3
    
    char* rle = rle_encode(test);

    printf("%s => %s\n", test, rle);
    printf("%s => %s\n", rle, rle_decode(rle));


    return 0;
}

/*
   | 'Failed.
   | Encode Test : KO
   | Result != 9A1A1C4B
   | You provided :
   | A:C1B4   8'
*/