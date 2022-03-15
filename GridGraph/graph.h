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
