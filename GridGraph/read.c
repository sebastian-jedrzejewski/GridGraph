#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "read.h"
#include "bfs.h"

#define MAX_LINE_LEN 1024


int path_fill(d_result result, int *nv, int from, int to)
{
    int l = 0;
    int i;
    for(i = to; i > -1; i = result->p[i])
        nv[l++] = i;
    
    if(nv[l-1] != from)
        return -1;
    return l;
}

void path_display(d_result result, int *nv, int l)
{
    int j;
    for(j = l-1; j >= 0; j--)
    {
        if(j != 0)
            printf("%d - ", nv[j]);
        else
            printf("%d ", nv[j]);
    }
}

void bfs_init(graph g)
{
    int *visited = bfs(g, 0);
    int c = 0;
    while(visited[c++] && c < g->height * g->width)
        ;
    if(c == g->height * g->width)
        printf("Connectivity: connected\n\n");
    else
        printf("Connectivity: disconnected\n\n");
}

void dijkstra_init(graph g, int vertex_a, int vertex_b)
{
    int i, j, l;
    d_result result = dijkstra(g, vertex_a, vertex_b);

    int *nv = malloc(g->height * g->width * sizeof *nv);

    if(vertex_b >= 0)
    {
        printf("Shortest path from %d to %d and its weight: ", vertex_a, vertex_b);
        l = path_fill(result, nv, vertex_a, vertex_b);
        if(l > 0)
        {
            path_display(result, nv, l);
            printf("(%g)\n", result->d[vertex_b]);
        }
        else
            printf("Path does not exist\n");
    }
    else
    {
        printf("Shortest paths from %d to all vertices and their weights:\n\n", vertex_a);
        for(i = 0; i < g->height * g->width; i++)
        {
            l = path_fill(result, nv, vertex_a, i);
            printf("Path to %d (weight): ", i);
            if(l > 0)
            {
                path_display(result, nv, l);
                printf("(%g)\n", result->d[i]);
            }
            else
                printf("Path does not exist\n");
        }
    }

    result_free(result);
    free(nv);
}

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
    {
        if(vertex_a >= g->height * g->width || vertex_b >= g->height * g->width)
        {
            fprintf(stderr, "ERROR (Read mode): Number of vertex in shortest_path_a is greater than total number of vertices [SHORTEST_PATH_A_GREATER_THAN_TOTAL_NUMBER_OF_VERTICES]\n");
            return EXIT_FAILURE;
        }
        if (vertex_b >= g->height * g->width)
        {
            fprintf(stderr, "ERROR (Read mode): Number of vertex in shortest_path_b is greater than total number of vertices [SHORTEST_PATH_B_GREATER_THAN_TOTAL_NUMBER_OF_VERTICES]\n");
            return EXIT_FAILURE;
        }
        
        if(connectivity == 1)
        {
            bfs_init(g);
        }

        if(vertex_a >= 0)
        {
            dijkstra_init(g, vertex_a, vertex_b);
        }

        return 0;
    }
}