#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

typedef struct p
{
    int *q; // numbers of vertices; priority is the smallest weight to reach the vertex from the source
    int *pn; // positions of vertices in q
    int n; // number of elements in q
    int size; // max size of q (number of vertices in the graph)
} *pq;

pq pq_init(int size);
int pq_is_empty(pq p_queue);
int pq_push(pq p_queue, double *d, int v);
int pq_pop(pq p_queue, double *d);
void heap_up(pq p_queue, double *d, int from);
void pq_free(pq p_queue);

#endif