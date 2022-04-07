#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "priority_queue.h"

int main(int argc, char *argv[])
{
    int n = argc > 1 ? atoi(argv[1]) : 10;
    FILE *f = argc > 2 ? fopen(argv[2], "w") : stdout;
    double *d = malloc(n * sizeof *d);
    pq p_queue = pq_init(n);
    
    srand(time(NULL));
    int i;
    for(i = 0; i < n; i++)
    {
        d[i] = (double) rand() / RAND_MAX;
        p_queue->pn[i] = 0; // this array isn't used during tests but it is initialised here
        //printf("Drawn: %g\n", d[i]);
    }

    for(i = 0; i < n; i++)
    {
        if(pq_push(p_queue, d, i))
            return EXIT_FAILURE;
    }

    fprintf(f, "Heap sort:\n");
    while(!pq_is_empty(p_queue))
    {
        fprintf(f, "%g\n", d[pq_pop(p_queue, d)]);
    }

    pq_free(p_queue);

    return EXIT_SUCCESS;

}