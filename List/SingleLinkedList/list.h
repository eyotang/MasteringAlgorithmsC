/* list.h */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Define a structure for linked list elements. */
typedef struct ListElmt_
{
    void *data;
    struct ListElmt_ *next;
} ListElmt;


/* Define a structrue for linked lists. */
typedef struct List_
{
    int  (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    int size;
    ListElmt *head;
    ListElmt *tail;
} List;

/* Public interfaces */
void list_init(List *list, void (*destroy)(void *data), int (*compare)(const void *key1, const void *key2));
void list_destroy(List *list);
int list_find_prev(List *list, ListElmt **element, const void *data);
int list_ins_next(List *list, ListElmt *element, const void *data);
int list_rm_next(List *list, ListElmt *element, void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? true : false)
#define list_is_tail(list, element) ((element) == (list)->tail ? true : false)
#define list_is_empty(list) (((list)->size == 0) ? true : false)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)


#endif // LIST_H
