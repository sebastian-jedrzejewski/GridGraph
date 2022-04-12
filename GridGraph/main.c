#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "helpers.h"
#include "read.h"
#include "write.h"


// OPTIONS { long (--), short (-) }
const char* write_o[2] = { "--write", "-w" };
const char* w_width_o[2] = { "--width", "-xw" };
const char* w_height_o[2] = { "--height", "-xh" };
const char* w_edge_weight_min_o[2] = { "--edge_weight_min", "-Wmin" };
const char* w_edge_weight_max_o[2] = { "--edge_weight_max", "-Wmax" };
const char* w_edge_count_min_o[2] = { "--edge_count_min", "-Cmin" };
const char* w_edge_count_max_o[2] = { "--edge_count_max", "-Cmax" };
const char* w_seed_o[2] = { "--seed", "-s" };

const char* read_o[2] = { "--read", "-r" };
const char* r_connectivity_o[2] = { "--connectivity", "-c" };
const char* r_shortest_path_a_o[2] = { "--shortest_path_a", "-sA" };
const char* r_shortest_path_b_o[2] = { "--shortest_path_b", "-sB" };

const char* file_o[2] = { "--file", "-f" };

// HELP
const char* help =
"usage: gridgraph [mode] [mode options] [file]\n"
"\n"
"Mode switches:\n"
"--write/-w                 write mode (generates graph with specified parameters and saves it to file/writes it to stdout)\n"
"--read/-r                  read mode (reads graph from file/stdin and checks specified parameters)\n"
"\n"
"Write mode options (* = optional):\n"
"--width/-xw                graph width (number of colums) [must be integer]\n"
"--height/-xh               graph height (number of rows) [must be integer]\n"
"--edge_weight_min/-Wmin    *edge weight randomizer lower bound [must be >=0; default: 0]\n"
"--edge_weight_max/-Wmax    *edge weight randomizer upper bound [must be >=edge_weight_min & ; default: 1]\n"
"--edge_count_min/-Cmin     *single-vertex edge count randomizer lower bound (not guaranteed) [must be >=0 & <=edge_count_max & integer; default: 0]\n"
"--edge_count_max/-Cmax     *single-vertex edge count randomizer upper bound [must be <=4 & >=edge_count_min & integer; default: 4]\n"
"--seed/-s                  *custom randomizer seed [must be integer]"
"\n"
"Read mode options (at least one required; ~ = switch):\n"
"--connectivity/-c          ~check connectivity\n"
"--shortest_path_a/-sA      find shortest path from specified point to the remaining vertices\n"
"--shortest_path_b/-sB      [requires shortest_path_a] find shortest path from point a (specified in shortest_path_a) to point b (specified here)\n"
"\n"
"File option:\n"
"--file/-f                  path to file where the graph has to be written/read from (if not specified program will use stdout/stdin)\n";


// WRITE MODE INIT
int write_init(int argc, char* argv[])
{
    int width = -1; // Must be specified (>0)
    int height = -1; // Must be specified (>0)
    double edge_weight_min = 0;
    double edge_weight_max = 1;
    int edge_count_min = 0;
    int edge_count_max = 4;
    int seed = time(0);
    FILE* file = NULL;

    // Get values
    for (int i = 1; i < argc; i++)
    {
        // width
        if (str_arr_get_index(argv[i], w_width_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_int(argv[i])) 
            {
                width = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): width must be a number (integer) [WIDTH_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // height
        else if (i < argc && str_arr_get_index(argv[i], w_height_o, 2) >= 0)
        {
            i++;
            if (str_is_int(argv[i])) 
            {
                height = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): height must be a number (integer) [HEIGHT_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // edge_weight_min
        else if (str_arr_get_index(argv[i], w_edge_weight_min_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_double(argv[i])) 
            {
                edge_weight_min = atof(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): edge_weight_min must be a number [EDGE_WEIGHT_MIN_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // edge_weight_max
        else if (str_arr_get_index(argv[i], w_edge_weight_max_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_double(argv[i])) 
            {
                edge_weight_max = atof(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): edge_weight_max must be a number [EDGE_WEIGHT_MAX_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // edge_count_min
        else if (str_arr_get_index(argv[i], w_edge_count_min_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_int(argv[i])) 
            {
                edge_count_min = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): edge_count_min must be a number (integer) [EDGE_COUNT_MIN_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // edge_count_min
        else if (str_arr_get_index(argv[i], w_edge_count_max_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_int(argv[i])) 
            {
                edge_count_max = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): edge_count_max must be a number (integer) [EDGE_COUNT_MAX_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // seed
        else if (str_arr_get_index(argv[i], w_seed_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_int(argv[i])) 
            {
                seed = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Write mode): seed must be a number (integer) [SEED_NOT_A_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // file
        else if (str_arr_get_index(argv[i], file_o, 2) >= 0)
        {
            i++;
            if (i < argc)
            {
                file = fopen(argv[i], "w");
            }
        }
    }

    // Check values
    if (width <= 0)
    {
        fprintf(stderr, "ERROR (Write mode): width must be greater than 0 (%d was given) [WIDTH_LOWER_OR_EQUAL_TO_ZERO]\n", width);
        return EXIT_FAILURE;
    }
    if (height <= 0)
    {
        fprintf(stderr, "ERROR (Write mode): height must be greater than 0 (%d wag given) [HEIGHT_LOWER_OR_EQUAL_TO_ZERO]\n", height);
        return EXIT_FAILURE;
    }
    if (edge_weight_min < 0)
    {
        fprintf(stderr, "ERROR (Write mode): edge_weight_min must be greater or equal to 0 (%f was given) [EDGE_WEIGHT_MIN_LOWER_THAN_ZERO]\n", edge_weight_min);
        return EXIT_FAILURE;
    }
    if (edge_weight_min > edge_weight_max)
    {
        fprintf(stderr, "ERROR (Write mode): edge_weight_min (%f was given) must be lower or equal to edge_weight_max (%f was given) [EDGE_WEIGHT_MIN_GREATER_THAN_EDGE_WEIGHT_MAX]\n", edge_weight_min, edge_weight_max);
        return EXIT_FAILURE;
    }
    if (edge_count_min < 0)
    {
        fprintf(stderr, "ERROR (Write mode): edge_count_min must be greater or equal to 0 (%d was given) [EDGE_COUNT_MIN_LOWER_THAN_ZERO]\n", edge_count_min);
        return EXIT_FAILURE;
    }
    if (edge_count_max > 4)
    {
        fprintf(stderr, "ERROR (Write mode): edge_count_max must be lower or equal to 4 (%d was given) [EDGE_WEIGHT_MAX_GREATER_THAN_FOUR]\n", edge_count_max);
        return EXIT_FAILURE;
    }
    if (edge_count_min > edge_count_max)
    {
        fprintf(stderr, "ERROR (Write mode): edge_count_min (%d was given) must be lower or equal to edge_count_max (%d was given) [EDGE_COUNT_MIN_GREATER_THAN_EDGE_COUNT_MAX]\n", edge_count_min, edge_count_max);
        return EXIT_FAILURE;
    }
    if (file == NULL)
    {
        file = stdout;
    }
    return write(file, width, height, edge_weight_min, edge_weight_max, edge_count_min, edge_count_max, seed);
}

// READ MODE INIT
int read_init(int argc, char* argv[])
{
    int connectivity = 0;
    int shortest_path_a = -1;
    int shortest_path_b = -1;
    FILE* file = NULL;

    // Get values
    for (int i = 1; i < argc; i++)
    {
        // connectivity
        if (str_arr_get_index(argv[i], r_connectivity_o, 2) >= 0)
        {
            connectivity = 1;
        }

        // shortest_path_a
        if (str_arr_get_index(argv[i], r_shortest_path_a_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_int(argv[i])) 
            {
                shortest_path_a = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Read mode): shortest_path_a must be a positive number [SHORTEST_PATH_A_NOT_POSITIVE_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // shortest_path_b
        if (str_arr_get_index(argv[i], r_shortest_path_b_o, 2) >= 0)
        {
            i++;
            if (i < argc && str_is_int(argv[i])) 
            {
                shortest_path_b = atoi(argv[i]);
            }
            else
            {
                fprintf(stderr, "ERROR (Read mode): shortest_path_b must be a positive number [SHORTEST_PATH_B_NOT_POSITIVE_NUMBER]\n");
                return EXIT_FAILURE;
            }
        }

        // file
        else if (str_arr_get_index(argv[i], file_o, 2) >= 0)
        {
            i++;
            if (i < argc)
            {
                file = fopen(argv[i], "r");
            }
        }
    }

    // Check values
    int at_least_one_option_chosen = 0;
    if (connectivity)
    {
        at_least_one_option_chosen = 1;
    }
    if (shortest_path_a >= 0)
    {
        at_least_one_option_chosen = 1;
    }
    if (shortest_path_b >= 0)
    {
        if (shortest_path_a < 0)
        {
            fprintf(stderr, "ERROR (Read mode): shortest_path_a argument is required when shortest_path_b is specified [SHORTEST_PATH_B_WITHOUT_SHORTEST_PATH_A_SPECIFIED]\n");
            return EXIT_FAILURE;
        }
        else if (shortest_path_b == shortest_path_a)
        {
            fprintf(stderr, "ERROR (Read mode): shortest_path_b (%d was given) cannot be equal to shortest_path_a (%d was given) [SHORTEST_PATH_B_EQUAL_TO_SHORTEST_PATH_A]\n", shortest_path_b, shortest_path_a);
            return EXIT_FAILURE;
        }
    }
    if (!at_least_one_option_chosen)
    {
        fprintf(stderr, "ERROR (Read mode): At least one of checking options has to be chosen [CHECKING_OPTION_NOT_SPECIFIED]\n");
        return EXIT_FAILURE;
    }
    if (file == NULL)
    {
        file = stdin;
    }

    return read(file, connectivity, shortest_path_a, shortest_path_b);
}

// ENTRY POINT
int main(int argc, char* argv[]) 
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (str_arr_get_index(argv[i], write_o, 2) >= 0)
            {
                return write_init(argc, argv);
            }
            else if (str_arr_get_index(argv[i], read_o, 2) >= 0)
            {
                return read_init(argc, argv);
            }
        }
        fprintf(stdout, "%s", help);
        return EXIT_FAILURE;
    }
    else
    {
        fprintf(stdout, "%s", help);
        return EXIT_FAILURE;
    }
}