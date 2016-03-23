/* list.h */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdarg.h>


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
void list_init_impl(List *list, void (*destroy)(void *data), int (*compare)(const void *key1, const void *key2));
void list_destroy(List *list);
int list_find_elmt(List *list, ListElmt **element, const void *data);
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

void list_init_arg(List *list, int count, ...);

#define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _
#define COUNT_PARMS(...)\
        COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define list_init(list, ...)                                         \
    list_init_arg(list, COUNT_PARMS(__VA_ARGS__), __VA_ARGS__)

#endif /* LIST_H */
