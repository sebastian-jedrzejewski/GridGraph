#include <stdlib.h>
#include <time.h>

#include "helpers.h"


// DRAW RANDOM INTEGER FROM RANGE
int rand_range_int(int lower, int upper)
{
    // Set seed
    srand(time(0));

    // Draw and return
    return (rand() % (upper - lower + 1)) + lower;
}