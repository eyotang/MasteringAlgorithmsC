/* queue.c */

#include <stdlib.h>

#include "list.h"
#include "queue.h"

/* queue push */
int queue_push(Queue *queue, void *data)
{
    return list_ins_next(queue, list_tail(queue), data);
}

/* queue pop */
int queue_pop(Queue *queue, void **data)
{
    return list_rm_next(queue, NULL, data);
}
