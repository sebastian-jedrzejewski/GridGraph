#ifndef _QUEUE_H_
#define _QUEUE_H_

// STRUCTS DECLARATIONS
typedef struct q
{
    int value;
    struct q* next;
} queue;

// FUNCTIONS DECLARATIONS
void queue_enqueue(queue** q, int value);
int queue_dequeue(queue** q);

#endif