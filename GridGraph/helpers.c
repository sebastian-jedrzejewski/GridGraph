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

// CHECK IF STRING IS INT
int str_is_int(char* string)
{
    int i = 0;
    if (string[i] == '-') i++;
    if (string[i] == '\0') return 0;
    for (i; string[i] != '\0'; i++)
    {
        if (!(string[i] >= '0' && string[i] <= '9'))
        {
            return 0;
        }
    }
    return 1;
}

// CHECK IF STRING IS DOUBLE
int str_is_double(char* string)
{
    int i = 0;
    if (string[i] == '-') i++;
    if (string[i] == '\0') return 0;
    int dot = 0;
    for (i; string[i] != '\0'; i++)
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