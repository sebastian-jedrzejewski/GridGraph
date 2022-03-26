#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "read.h"
#include "write.h"


#define WRITE_LONG "--write"
#define WRITE_SHORT "-w"
#define W_WIDTH_LONG "--width"
#define W_WIDTH_SHORT "-xw"
#define W_HEIGHT_LONG "--height"
#define W_HEIGHT_SHORT "-xh"
#define W_EDGE_WEIGHT_MIN_LONG "--edge_weight_min"
#define W_EDGE_WEIGHT_MIN_SHORT "-Wmin"
#define W_EDGE_WEIGHT_MAX_LONG "--edge_weight_max"
#define W_EDGE_WEIGHT_MAX_SHORT "-Wmax"
#define W_EDGE_COUNT_MIN_LONG "--edge_count_min"
#define W_EDGE_COUNT_MIN_SHORT "-Cmin"
#define W_EDGE_COUNT_MAX_LONG "--edge_count_max"
#define W_EDGE_COUNT_MAX_SHORT "-Cmax"

#define READ_LONG "--read"
#define READ_SHORT "-r"
#define R_CONNECTIVITY_LONG "--check_connectivity"
#define R_CONNECTIVITY_SHORT "-c"
#define R_SHORTEST_PATH_A_LONG "--shortest_path_a"
#define R_SHORTEST_PATH_A_SHORT "-sA"
#define R_SHORTEST_PATH_B_LONG "--shortest_path_b"
#define R_SHORTEST_PATH_B_SHORT "-sB"

#define FILE_LONG "--file"
#define FILE_SHORT "-f"



// GET ARGUMENT INDEX
int get_arg_index(int argc, char* argv[], char* long_name, char* short_name)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], long_name) == 0 || strcmp(argv[i], short_name) == 0)
        {
            return i;
        }
    }
    return 0;
}


// WRITE MODE INIT
int start_write(int argc, char* argv[])
{
    int width = 0; // Must be >0
    int height = 0; // Must be >0
    double edge_weight_min = 0; // Must be >=0 && <=edge_weight_max
    double edge_weight_max = 1; // Must be >=edge_weight_min
    int edge_count_min = 0; // Must be >=0 && <=edge_count_max
    int edge_count_max = 4; // Must be >=edge_count_min && <=4

    // Get width
    int width_index = get_arg_index(argc, argv, W_WIDTH_LONG, W_WIDTH_SHORT);
    if (width_index > 0 && argc > width_index)
    {
        width = atoi(argv[width_index + 1]);
    }
    else
    {
        fprintf(stderr, "ERROR (Write mode): Width argument not found");
        return EXIT_FAILURE;
    }

    // Get height
    int height_index = get_arg_index(argc, argv, W_HEIGHT_LONG, W_HEIGHT_SHORT);
    if (height_index > 0 && argc > height_index)
    {
        height = atoi(argv[height_index + 1]);
    }
    else
    {
        fprintf(stderr, "ERROR (Write mode): Height argument not found");
        return EXIT_FAILURE;
    }

    // Get edge_weight_min
    int edge_weight_min_index = get_arg_index(argc, argv, W_EDGE_WEIGHT_MIN_LONG, W_EDGE_WEIGHT_MIN_SHORT);
    if (edge_weight_min_index > 0 && argc > edge_weight_min_index)
    {
        edge_weight_min = atof(argv[edge_weight_min_index + 1]);
    }

    // Get edge_weight_max
    int edge_weight_max_index = get_arg_index(argc, argv, W_EDGE_WEIGHT_MAX_LONG, W_EDGE_WEIGHT_MAX_SHORT);
    if (edge_weight_max_index > 0 && argc > edge_weight_max_index)
    {
        edge_weight_max = atof(argv[edge_weight_max_index + 1]);
    }

    // Get edge_count_min
    int edge_count_min_index = get_arg_index(argc, argv, W_EDGE_COUNT_MIN_LONG, W_EDGE_COUNT_MIN_SHORT);
    if (edge_count_min_index > 0 && argc > edge_count_min_index)
    {
        edge_count_min = atoi(argv[edge_count_min_index + 1]);
    }

    // Get edge_count_max
    int edge_count_max_index = get_arg_index(argc, argv, W_EDGE_COUNT_MAX_LONG, W_EDGE_COUNT_MAX_SHORT);
    if (edge_count_max_index > 0 && argc > edge_count_max_index)
    {
        edge_count_max = atoi(argv[edge_count_max_index + 1]);
    }

    // Check arguments
    if (width <= 0)
    {
        fprintf(stderr, "ERROR (Write mode): Width must be greater than 0.");
        return EXIT_FAILURE;
    }
    if (height <= 0)
    {
        fprintf(stderr, "ERROR (Write mode): Height must be greater than 0.");
        return EXIT_FAILURE;
    }
    if (edge_weight_min < 0)
    {
        fprintf(stderr, "ERROR (Write mode): Minimum weight of edges must be greater than or equal to 0.");
        return EXIT_FAILURE;
    }
    if (edge_weight_max < edge_weight_min)
    {
        fprintf(stderr, "ERROR (Write mode): Maximum weight of edges must be greater than or equal to minimum weight of edges.");
        return EXIT_FAILURE;
    }
    if (edge_count_min < 0)
    {
        fprintf(stderr, "ERROR (Write mode): Minimum number of edges must be greater than or equal to 0.");
        return EXIT_FAILURE;
    }
    if (edge_count_max > 4)
    {
        fprintf(stderr, "ERROR (Write mode): Maximum number of edges must be less than or equal to 4.");
        return EXIT_FAILURE;
    }
    if (edge_count_max < edge_count_min)
    {
        fprintf(stderr, "ERROR (Write mode): Maximum number of edges must be greater than or equal to minimum number of edges.");
        return EXIT_FAILURE;
    }

    // Get file
    FILE* file = NULL;
    int file_index = get_arg_index(argc, argv, FILE_LONG, FILE_SHORT);
    if (file_index > 0 && argc > file_index)
    {
        file = fopen(argv[file_index + 1], "w");
    }
    if (file == NULL)
    {
        file = stdout;
    }

    return write(file, width, height, edge_weight_min, edge_weight_max, edge_count_min, edge_count_max);
}


// READ MODE INIT
int start_read(int argc, char* argv[])
{
    int connectivity = 0;
    int vertex_a = -1;
    int vertex_b = -1;

    // Connectivity
    int connectivity_index = get_arg_index(argc, argv, R_CONNECTIVITY_LONG, R_CONNECTIVITY_SHORT);
    if (connectivity_index > 0)
    {
        connectivity = 1;
    }

    // Get vertex_a
    int vertex_a_index = get_arg_index(argc, argv, R_SHORTEST_PATH_A_LONG, R_SHORTEST_PATH_A_SHORT);
    if (vertex_a_index > 0 && argc > vertex_a_index)
    {
        vertex_a = atoi(argv[vertex_a_index + 1]);
    }

    // Get vertex_b
    int vertex_b_index = get_arg_index(argc, argv, R_SHORTEST_PATH_B_LONG, R_SHORTEST_PATH_B_SHORT);
    if (vertex_b_index > 0 && argc > vertex_b_index)
    {
        vertex_b = atoi(argv[vertex_b_index + 1]);
    }

    // Get file
    FILE* file = NULL;
    int file_index = get_arg_index(argc, argv, FILE_LONG, FILE_SHORT);
    if (file_index > 0 && argc > file_index)
    {
        file = fopen(argv[file_index + 1], "r");
    }
    if (file == NULL)
    {
        file = stdin;
    }

    return read(file, connectivity, vertex_a, vertex_b);
}


// ENTRY POINT
int main(int argc, char* argv[]) 
{
    if (argc > 1)
    {
        int write_mode = get_arg_index(argc, argv, WRITE_LONG, WRITE_SHORT);
        int read_mode = get_arg_index(argc, argv, READ_LONG, READ_SHORT);
        if (write_mode > 0 && read_mode == 0)
        {
            return start_write(argc, argv);
        }
        else if (read_mode > 0 && write_mode == 0)
        {
            return start_read(argc, argv);
        }
        else
        {
            fprintf(stderr, "ERROR: Invalid combination of modes.");
            return EXIT_FAILURE;
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Invalid number of arguments.");
        return EXIT_FAILURE;
    }
}