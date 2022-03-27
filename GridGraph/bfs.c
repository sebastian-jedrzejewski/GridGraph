#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "bfs.h"
#include "graph.h"
#include "queue.h"


// MAIN BFS ALGORITHM
int* bfs(graph graph, int vertex)
{
    // Init for all vertices
    int number_of_vertices = graph->height * graph->width;
    int* visited = malloc(sizeof(int) * number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        visited[i] = 0;
    }

    // Init for start vertex
    visited[vertex] = 1;

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
            if (!visited[v])
            {
                visited[v] = 1;
                queue_enqueue(&queue, v);
            }
            current_vertex_edges = current_vertex_edges->next;
        }
        visited[current_vertex] = 1;
    }

    return visited;
}