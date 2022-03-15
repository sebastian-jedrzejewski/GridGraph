#ifndef GRAPH_H
#define GRAPH_H

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

graph initialize_graph(int w, int h);
edge_list* add_edge(edge_list *l, int v, double wt);
void free_graph(graph g);

#endif