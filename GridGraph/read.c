#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "read.h"

#define MAX_LINE_LEN 1024
#define MAX_VERTICES_IN_LINE 128



// Manages the read mode
int read(FILE *file, int connectivity, int vertex_a, int vertex_b)
{   
    graph g = read_graph(file);
    if(g == NULL)
        return 1;
    else
        return 0;
}


// Reads a graph from a file and saves it to the structure
graph read_graph(FILE *f)
{
    int c, r, i;
    if(fscanf(f, "%d %d", &c, &r) != 2)
        return NULL;

    graph g = graph_init(c, r);

    char buf[MAX_LINE_LEN];
    int *vertices = malloc(MAX_VERTICES_IN_LINE * sizeof *vertices);
    double *weights = malloc(MAX_VERTICES_IN_LINE * sizeof *weights);
    int index = 0;
    int count = 0;
    int offset;
    char *new_edge;

    while(fgets(buf, MAX_LINE_LEN, f) != NULL)
    {
        new_edge = buf;
        index = 0;
        while(sscanf(new_edge, "%d :%lf%n", vertices + index, weights + index, &offset) == 2) {
            index++;
            new_edge += offset;
        }
        
        for(i = 0; i < index; i++) {
            if(count >= r * c)
                return NULL;
            g->list[count] = edge_list_add(g->list[count], vertices[i], weights[i]);
        }
        
        count++;
    }
    free(vertices);
    free(weights);
    return g;
}