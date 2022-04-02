#ifndef _READ_H_
#define _READ_H_

#include <stdio.h>
#include "dijkstra.h"

// FUNCTIONS DECLARATIONS
int read(FILE *file, int connectivity, int vertex_a, int vertex_b);
graph read_graph(FILE *f);
int path_fill(d_result result, int *nv, int from, int to);
void path_display(int *nv, int l);
void bfs_init(graph g);
void dijkstra_init(graph g, int vertex_a, int vertex_b);

#endif