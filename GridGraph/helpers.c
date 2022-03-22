#include <stdlib.h>
#include <time.h>

#include "helpers.h"



// REMOVE ELEMENT AT INDEX FROM ARRAY (INT)
void int_array_remove_at(int* array, int length, int index)
{
    int i;
    for(i = index; i < length - 1; i++)
    {
        array[i] = array[i + 1];
    }
}