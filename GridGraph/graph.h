#ifndef GRAPH_H
#define GRAPH_H

// STRUCTS DECLARATIONS
typedef struct e {
	int vertex;
	double weight;
	struct e *next;
} edge_list;
typedef struct g {
	int width;
	int height;
	edge_list **list;
} *graph;

// FUNCTIONS DECLARATIONS
graph graph_init(int w, int h);
edge_list* edge_list_add(edge_list *l, int v, double wt);
int edge_list_contains_vertex(edge_list* l, int v);
int edge_list_length(edge_list* l);
void graph_free(graph g);

#endif