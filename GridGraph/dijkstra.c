#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dijkstra.h"

d_result result_init(int n, int vertex_a, int *visited)
{
    d_result result = malloc(sizeof *result);
    result->d = malloc(n * sizeof *(result->d));
    result->p = malloc(n * sizeof *(result->p));

    int i;
    for(i = 0; i < n; i++)
    {
        *visited = 0;
        if(i == vertex_a)
            result->d[i] = 0;
        else
            result->d[i] = INT_MAX;
        result->p[i] = -1;
        visited++;
    }
    return result;
}

void result_free(d_result result)
{
    free(result->d);
    free(result->p);
    free(result);
}

d_result dijkstra(graph graph, int vertex_a, int vertex_b)
{
    int n = graph->height * graph->width;
    int *visited = malloc(n * sizeof *visited);

    int i, j, x;
    edge_list *iter = NULL;

    d_result result = result_init(n, vertex_a, visited);

    for(i = 0; i < n; i++)
    {
        for(j = 0; visited[j]; j++)
            ;
        
        x = j;
        for(j = x; j < n; j++)
            if(result->d[j] < result->d[x] && !visited[j])
             x = j;
        
        visited[x] = 1;

        
        iter = graph->list[x];
        while(iter != NULL)
        {
            if(visited[iter->vertex])
            {
                iter = iter->next;
                continue;
            }
            else
                if(result->d[iter->vertex] > result->d[x] + iter->weight)
                    result->d[iter->vertex] = result->d[x] + iter->weight;
            result->p[iter->vertex] = x;
            iter = iter->next;
        }
    }
    return result;
}
