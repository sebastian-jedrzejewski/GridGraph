#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "bfs.h"
#include "graph.h"
#include "queue.h"


// COLOR
typedef enum c 
{
    white = 0,
    grey = 1,
    black = 2,
} color;


// MAIN BFS ALGORITHM
void bfs(graph graph, int vertex)
{
    // Init for all vertices
    int number_of_vertices = graph->height * graph->width;
    color* colors = malloc(sizeof(color) * number_of_vertices);
    int* parents = malloc(sizeof(int) * number_of_vertices);
    int* lengths = malloc(sizeof(int) * number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        colors[i] = white;
        lengths[i] = INT_MAX;
        parents[i] = 0;
    }

    // Init for start vertex
    colors[vertex] = grey;
    lengths[vertex] = 0;

    // Init queue
    queue* queue = NULL;
    queue_enqueue(&queue, vertex);

    int current_vertex;
    while (queue != NULL)
    {
        current_vertex = queue_dequeue(&queue);
        edge_list* current_vertex_edges = graph->list[current_vertex];
        while (current_vertex_edges != NULL)
        {
            int v = current_vertex_edges->vertex;
            if (colors[v] == white)
            {
                colors[v] = grey;
                lengths[v] = lengths[current_vertex] + 1;
                parents[v] = current_vertex;
                queue_enqueue(&queue, v);
            }
            current_vertex_edges = current_vertex_edges->next;
        }
        colors[current_vertex] = black;
    }
}