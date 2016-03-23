/* dlist.h */

#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>
#include <stdarg.h>


/* Define a structure for doubly-linked list elements. */
typedef struct DListElmt_
{
    void *data;
    struct DListElmt_ *prev;
    struct DListElmt_ *next;
} DListElmt;


/* Define a struct for doubly-linked lists. */
typedef struct DList_
{
    int size;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    DListElmt *head;
    DListElmt *tail;
} DList;


/* Public interface */
void dlist_init_impl(DList *list, void (*destroy)(void *data), int (*compare)(const void *key1, const void *key2));
void dlist_destroy(DList *list);
int dlist_find_elmt(DList *list, DListElmt **element, const void *data);
int dlist_ins_next(DList *list, DListElmt *element, const void *data);
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);
int dlist_remove(DList *list, DListElmt *element, void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(list, element) ((element) == (list)->head ? true : false)
#define dlist_is_tail(list, element) ((element) == (list)->tail ? true : false)
#define dlist_is_empty(list) (((list)->size == 0) ? true : false)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

void dlist_init_arg(DList *list, int count, ...);

#define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _
#define COUNT_PARMS(...)\
        COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define dlist_init(list, ...)                                         \
    dlist_init_arg(list, COUNT_PARMS(__VA_ARGS__), __VA_ARGS__)


#endif /* DLIST_H */
