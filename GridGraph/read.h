#ifndef _READ_H_
#define _READ_H_

#include <stdio.h>

int read(char *file, int connectivity, int vertex_a, int vertex_b);
graph read_graph(FILE *f);

#endif