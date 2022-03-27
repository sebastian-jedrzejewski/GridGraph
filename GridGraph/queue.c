#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


// ENQUEUE
void queue_enqueue(queue** q, int value)
{
    queue* new_entry = malloc(sizeof(queue));
    new_entry->value = value;
    new_entry->next = *q;

    *q = new_entry;
}

// DEQUEUE
int queue_dequeue(queue** q)
{
    queue* head = NULL;
    queue* prev = NULL;
    int value = -1;

    if (*q != NULL)
    {
        head = *q;
        while (head->next != NULL)
        {
            prev = head;
            head = head->next;
        }
        value = head->value;
        free(head);
        if (prev)
        {
            prev->next = NULL;
        }
        else
        {
            *q = NULL;
        }
    }
    
    return value;
}