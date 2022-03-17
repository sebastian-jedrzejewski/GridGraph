#include <stdlib.h>

#include "graph.h"



// CREATE A NEW GRAPH
graph graph_init(int w, int h)
{
    graph g = malloc(sizeof *g);
    g->height = h;
    g->width = w;
    g->list = malloc(w * h * sizeof *(g->list));
    for (int i = 0; i < w * h; i++)
    {
        g->list[i] = NULL;
    }
    return g;
}

// ADD NEW EDGE TO SPECIFIED EDGE_LIST (VERTEX)
edge_list* edge_list_add(edge_list *l, int v, float wt)
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

// CHECK IF EDGE LIST CONTAINS SPECIFIED VERTEX
int edge_list_contains_vertex(edge_list* l, int v)
{
    if (l != NULL)
    {
        edge_list* cp_l = l;
        while (cp_l)
        {
            if (cp_l->vertex == v)
            {
                return 1;
            }
            else
            {
                cp_l = cp_l->next;
            }
        }
    }
    return 0;
}

// GET EDGE LIST LENGTH
int edge_list_length(edge_list* l)
{
    int counter = 0;
    if (l != NULL)
    {
        edge_list* cp_l = l;
        while (cp_l)
        {
            counter++;
            cp_l = cp_l->next;
        }
    }
    return counter;
}

// FREE UP MEMORY ALLOCATED FOR THE GRAPH
void graph_free(graph g)
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