#include <stdint.h>

void my_swap(int* first, int* second) 
{ 
    int temp = *first; 
    *first = *second; 
    *second = temp; 
} 

void my_sort(int arr[], unsigned int length) 
{ 
    int min = 0; 
  
    for (uint32_t i = 0; i < length - 1; i++)
    { 
        min = i; 
        for (uint32_t j = i + 1; j < length; j++) 
            if (arr[j] < arr[min]) 
                min = j; 
  
        my_swap(&arr[min], &arr[i]); 
    } 
} 
