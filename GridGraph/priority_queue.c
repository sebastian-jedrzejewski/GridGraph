#include <stdlib.h>
#include <stdio.h>

#include "priority_queue.h"

pq pq_init(int size)
{
    pq p_queue = malloc(sizeof *p_queue);
    p_queue->q = malloc(size * sizeof *(p_queue->q));
    p_queue->pn = malloc(size * sizeof *(p_queue->pn));
    p_queue->n = 0;
    p_queue->size = size;
    return p_queue;
}

int pq_is_empty(pq p_queue)
{
    return p_queue->n == 0;
}

void heap_up(pq p_queue, double *d, int from)
{
    int *q = p_queue->q;
    int *pn = p_queue->pn;
    int n = p_queue->n;
    
    int i = from;
    int p = (i - 1) / 2;
    int temp;
    while(i > 0)
    {
        if(d[q[i]] >= d[q[p]])
            break;
        
        temp = q[i];
        q[i] = q[p];
        q[p] = temp;
        pn[q[i]] = i;
        pn[q[p]] = p;

        i = p;
        p = (i-1) / 2;
    }
}

// Dijkstra's algorithm does not use this function, it is only for tests
int pq_push(pq p_queue, double *d, int v)
{
    if(p_queue->n == p_queue->size) // there is no need to increase the size which is the total number of vertices
        return -1;
    
    p_queue->q[p_queue->n++] = v;
    heap_up(p_queue, d, (p_queue->n)-1);
    
    return 0;
}

static void heap_down(pq p_queue, double *d)
{
    int *q = p_queue->q;
    int *pn = p_queue->pn;
    int n = p_queue->n;

    int i = 0;
    int c = 2*i + 1;
    int tmp;
    while(c < n)
    {
        if(c+1 < n && d[q[c]] > d[q[c+1]])
            c++;
        
        if(d[q[i]] <= d[q[c]])
            break;

        tmp = q[i];
        q[i] = q[c];
        q[c] = tmp;
        pn[q[i]] = i;
        pn[q[c]] = c;

        i = c;
        c = 2*i + 1;
    }
}

int pq_pop(pq p_queue, double *d)
{
    int u = p_queue->q[0];
    p_queue->q[0] = p_queue->q[--p_queue->n];
    heap_down(p_queue, d);
    return u;    
}

void pq_free(pq p_queue)
{
    free(p_queue->q);
    free(p_queue->pn);
    free(p_queue);
}