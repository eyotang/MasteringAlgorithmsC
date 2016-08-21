/* queue.h */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "list.h"

/* Implement queue as linked list. */
typedef List Queue;

/* Public interfaces. */
#define queue_init list_init
#define queue_destroy list_destroy

int queue_push(Queue *queue, void *data);
int queue_pop(Queue *queue, void **data);

#define queue_front(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
#define queue_size list_size

#endif /* QUEUE_H */
