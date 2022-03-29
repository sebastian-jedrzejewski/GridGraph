#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "write.h"



// CONSTANTS
const int ec_drawing_weight[5] = {1, 2, 4, 8, 16};


// GENERATE GRAPH
graph gen_graph(int width, int height, double edge_weight_min, double edge_weight_max, int edge_count_min, int edge_count_max)
{
    srand(time(0));

    // Sum of weights
    int ec_weight_sum = 0;
    for (int i = edge_count_min; i < edge_count_max + 1; i++)
    {
        ec_weight_sum += ec_drawing_weight[i];
    }

    // Create drawing array
    int* ec_drawing_array = malloc(sizeof(int) * ec_weight_sum);
    int* cp_ec_drawing_array = ec_drawing_array;
    for (int i = edge_count_min; i < edge_count_max + 1; i++)
    {
        int weight = ec_drawing_weight[i];
        while (weight)
        {
            *cp_ec_drawing_array = i;
            cp_ec_drawing_array++;
            weight--;
        }
    }

    // Draw number of edges for each vertex
    int* edge_count_array = malloc(sizeof(int) * width * height);
    for (int i = 0; i < width * height; i++)
    {
        edge_count_array[i] = ec_drawing_array[rand() % ec_weight_sum];
    }
    free(ec_drawing_array);

    // Initialize graph
    graph graph = graph_init(width, height);
    
    for (int i = 0; i < width * height; i++)
    {
        // Get available vertices
        int available_vertices[4];
        int available_vertices_count = 0;
        if (i % width != 0 && edge_list_length(graph->list[i-1]) < edge_count_array[i-1] && !edge_list_contains_vertex(graph->list[i], i - 1)) // Left (i-1)
        {
            available_vertices[available_vertices_count] = i - 1;
            available_vertices_count++;
        }
        if ((i + 1) % width != 0 && edge_list_length(graph->list[i+1]) < edge_count_array[i+1] && !edge_list_contains_vertex(graph->list[i], i + 1)) // Right (i+1)
        {
            available_vertices[available_vertices_count] = i + 1;
            available_vertices_count++;
        }
        if (i - width >= 0 && edge_list_length(graph->list[i-width]) < edge_count_array[i-width] && !edge_list_contains_vertex(graph->list[i], i - width)) // Up (i-width)
        {
            available_vertices[available_vertices_count] = i - width;
            available_vertices_count++;
        }
        if (i + width < width * height && edge_list_length(graph->list[i+width]) < edge_count_array[i+width] && !edge_list_contains_vertex(graph->list[i], i + width)) // Down (i+width)
        {
            available_vertices[available_vertices_count] = i + width;
            available_vertices_count++;
        }

        // Create edges
        while (edge_list_length(graph->list[i]) < edge_count_array[i] && available_vertices_count > 0)
        {
            int index = rand() % available_vertices_count;
            int vertex = available_vertices[index];
            
            memmove(available_vertices + index, available_vertices + index + 1, sizeof(int) * (available_vertices_count - (index + 1)));
            available_vertices_count--;

            double weight = ((double)rand() / RAND_MAX) * (edge_weight_max - edge_weight_min) + edge_weight_min;

            graph->list[i] = edge_list_add(graph->list[i], vertex, weight);
            graph->list[vertex] = edge_list_add(graph->list[vertex], i, weight);
        }
    }
    free(edge_count_array);

    return graph;
}

// MAIN WRITE MODE FUNCTION
int write(FILE* file, int width, int height, double edge_weight_min, double edge_weight_max, int edge_count_min, int edge_count_max) 
{
    // Generate graph
    graph graph = gen_graph(width, height, edge_weight_min, edge_weight_max, edge_count_min, edge_count_max);

    // Write graph to file
    fprintf(file, "%d %d\n", height, width);
    for (int i = 0; i < width * height; i++)
    {
        fprintf(file, "\t");
        edge_list* edge_list = graph->list[i];
        while (edge_list)
        {
            fprintf(file, " %d :%f ", edge_list->vertex, edge_list->weight);
            edge_list = edge_list->next;
        }
        fprintf(file, "\n");
    }

    // Free up memory allocated for the graph
    graph_free(graph);

    return EXIT_SUCCESS;
}