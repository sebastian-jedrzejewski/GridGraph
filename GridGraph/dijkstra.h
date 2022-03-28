#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph.h"

typedef struct r {
    double *d;
    int *p;
} *d_result;


d_result result_init(int n, int vertex_a, int *visited);
void result_free(d_result result);
d_result dijkstra(graph graph, int vertex_a, int vertex_b);

#endif