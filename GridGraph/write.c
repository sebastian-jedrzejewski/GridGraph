#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "helpers.h"
#include "write.h"


// MAIN WRITE MODE FUNCTION
void write(FILE* file, int width, int height, double edge_weight_min, double edge_weight_max, int edge_count_min, int edge_count_max) 
{

}

// GENERATE GRAPH
graph gen_graph(int width, int height, double edge_weight_min, double edge_weight_max, int edge_count_min, int edge_count_max)
{

}

// GET RANDOM NUMBER OF EDGES
int rand_edge_count(int min, int max)
{
    // Edges counts drawing weight
    const int ec_drawing_weight[5] = {1, 2, 4, 8, 16};

    // Sum of weights
    int weight_sum = 0;
    for (int i = min; i < max + 1; i++)
    {
        weight_sum += ec_drawing_weight[i];
    }

    // Create drawing array
    int* drawing_array = malloc(sizeof(int) * weight_sum);
    int* cp_drawing_array = drawing_array;
    for (int i = min; i < max + 1; i++)
    {
        int weight = ec_drawing_weight[i];
        while (weight)
        {
            *cp_drawing_array = i;
            cp_drawing_array++;
            weight--;
        }
    }

    // Draw
    int edge_count = drawing_array[rand_range_int(0, weight_sum)];

    // Free up memory
    free(drawing_array);

    return edge_count;
}