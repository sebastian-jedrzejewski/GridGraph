#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"
#include "graph.h"
#include "priority_queue.h"

d_result result_init(int n, int vertex_a)
{
    d_result result = malloc(sizeof *result);
    result->d = malloc(n * sizeof *(result->d));
    result->p = malloc(n * sizeof *(result->p));

    int i;
    for(i = 0; i < n; i++)
    {
        result->d[i] = INT_MAX;
        result->p[i] = -1;
    }
    return result;
}

void result_free(d_result result)
{
    free(result->d);
    free(result->p);
    free(result);
}

d_result dijkstra(graph graph, int vertex_a)
{
    int n = graph->height * graph->width;
    int *visited = malloc(n * sizeof *visited);

    int i, j, u;
    edge_list *iter = NULL;

    d_result result = result_init(n, vertex_a);

    pq p_queue = pq_init(n);

    // Heap set
    for(i = 0; i < n; i++)
    {
        p_queue->q[i] = i;
        p_queue->pn[i] = i;
    }
    p_queue->n = n;

    result->d[vertex_a] = 0;

    // Keeping heap properties
    p_queue->q[0] = p_queue->q[vertex_a];
    p_queue->q[vertex_a] = 0;
    p_queue->pn[0] = vertex_a;
    p_queue->pn[vertex_a] = 0;

    while(!pq_is_empty(p_queue))
    {
        int u = pq_pop(p_queue, result->d);

        iter = graph->list[u];
        while(iter != NULL)
        {
            if(result->d[iter->vertex] > result->d[u] + iter->weight) 
            {
                result->d[iter->vertex] = result->d[u] + iter->weight;
                result->p[iter->vertex] = u;
                heap_up(p_queue, result->d, p_queue->pn[iter->vertex]);
            }
            iter = iter->next;
        }
    }
    /*for(i = 0; i < n; i++)
    {
        printf("d[%d] = %g, p[%d] = %d\n", i, result->d[i], i, result->p[i]);
    }*/
    return result;
}