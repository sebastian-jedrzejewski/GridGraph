#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "read.h"

#define MAX_LINE_LEN 1024
#define MAX_VERTICES_IN_LINE 128



// Reads a graph from a file and saves it to the structure
graph read_graph(FILE *f)
{
    int c, r, i;
    if(fscanf(f, "%d %d", &c, &r) != 2)
        return NULL;

    graph g = graph_init(c, r);

    char buf[MAX_LINE_LEN];
    int vertex;
    double weight;
    int count = -1;
    int offset;
    char *new_edge;

    while(fgets(buf, MAX_LINE_LEN, f) != NULL)
    {
        if(count >= r * c)
                return NULL;

        new_edge = buf;
        while(sscanf(new_edge, "%d :%lf%n", &vertex, &weight, &offset) == 2) {
            g->list[count] = edge_list_add(g->list[count], vertex, weight);
            new_edge += offset;
        }
        
        count++;
    }
    return g;
}


// Manages the read mode
int read(FILE *file, int connectivity, int vertex_a, int vertex_b)
{   
    graph g = read_graph(file);
    if(g == NULL)
        return 1;
    else
        return 0;
}