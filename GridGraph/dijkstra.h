#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph.h"

// STRUCTS DECLARATIONS
typedef struct r
{
    double *d;
    int *p;
} *d_result;

// FUNCTIONS DECLARATIONS
d_result result_init(int n, int vertex_a);
void result_free(d_result result);
d_result dijkstra(graph graph, int vertex_a);

#endif