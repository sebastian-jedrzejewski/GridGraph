#include <stdlib.h>
#include "graph.h"

// Creates a new graph
graph initialize_graph(int w, int h)
{
    graph g = malloc(sizeof *g);
    g->height = h;
    g->width = w;
    g->list = malloc(w * h * sizeof *(g->list));
    return g;
}

// Adds a new edge to a list at specific index (vertex)
edge_list* add_edge(edge_list *l, int v, double wt)
{
    edge_list *ne = malloc(sizeof *ne);
    ne->vertex = v;
    ne->weight = wt;
    ne->next = NULL;

    if(l == NULL)
        return ne;
    else
    {
        edge_list *iter = l;
        while(iter->next != NULL)
            iter = iter->next;
        iter->next = ne;
        return l;
    }
}

// Frees up memory allocated for the graph
void free_graph(graph g)
{
    int i;
    edge_list *tmp1 = malloc(sizeof *tmp1);
    edge_list *tmp2 = malloc(sizeof *tmp2);
    for(i = 0; i < g->height * g->width; i++)
    {
        tmp1 = g->list[i];
        while(tmp1 != NULL)
        {
            tmp2 = tmp1;
            tmp1 = tmp1->next;
            free(tmp2);
        }
        free(g->list[i]);
    }
    free(tmp1);
    free(tmp2);
    free(g);
}