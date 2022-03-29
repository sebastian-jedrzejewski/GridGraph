#include <string.h>

#include "helpers.h"


// GET ELEMENT INDEX IN ARRAY (char*)
int str_arr_get_index(char* element, const char* array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (!strcmp(element, array[i]))
        {
            return i;
        }
    }
    return -1;
}

// CHECK IF STRING IS INT (positive)
int str_is_int(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (!(string[i] >= '0' && string[i] <= '9'))
        {
            return 0;
        }
    }
    return 1;
}

// CHECK IF STRING IS FLOAT (positive)
int str_is_float(char* string)
{
    int dot = 0;
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            continue;
        }
        else if (string[i] == '.' && !dot)
        {
            dot = 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}