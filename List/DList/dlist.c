/* dlist.c */

#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init_arg(DList *list, int count, ...)
{
    va_list v;
    va_start(v, count);

    void *destroy = NULL;
    void *compare = NULL;

    for (int i = 0; i < count; ++i)
    {
        switch (i)
        {
            case 0:
                destroy = va_arg(v, void *);
                break;
            case 1:
                compare = va_arg(v, void *);
                break;
            default:
                break;
        }
    }
    va_end(v);

    dlist_init_impl(list, (void (*)(void *))destroy, (int (*)(const void *, const void *))compare);
}

void dlist_init_impl(DList *list, void (*destroy)(void *data), int (*compare)(const void *key1, const void *key2))
{
    /* Initialize the list */
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    list->destroy = destroy;
    list->compare = compare;

    return;
}

void dlist_destroy(DList *list)
{
    void *data = NULL;

    /* Remove each element */
    while (dlist_size(list) > 0)
    {
        if ((dlist_remove(list, dlist_tail(list), (void **)&data) == 0) && (list->destroy != NULL))
        {
            /* Call a user-defined function to free dynamically allocated ata */
            list->destroy(data);
        }
    }

    /* No operation are allowed now, but clear the structure as precaution */
    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element = NULL;

    /* Do not allow a NULL element unless the list is empty. */
    if ((NULL == element) && (dlist_size(list) != 0))
    {
        return -1;
    }

    /* Allocate storage for the element. */
    new_element = (DListElmt *)malloc(sizeof(DListElmt));
    if (NULL == new_element)
    {
        return -1;
    }

    /* Insert the new element into the list. */
    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        /* Handle insertion when the list is empty. */
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        /* Handle insertion when the list is not empty */
        new_element->next = element->next;
        new_element->prev = element;

        if (element->next == NULL)
        {
            list->tail = new_element;
        }
        else
        {
            element->next->prev = new_element;
        }
        element->next = new_element;
    }

    list->size++;
    return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
    DListElmt *new_element = NULL;

    /* Do not allow a NULL element unless the list is empty. */
    if ((NULL == element) && (dlist_size(list) != 0))
    {
        return -1;
    }

    /* Allocate storage for the element. */
    new_element = (DListElmt *)malloc(sizeof(DListElmt));
    if (NULL == new_element)
    {
        return -1;
    }

    /* Insert the new element into the list. */
    new_element->data = (void *)data;

    if (dlist_size(list) == 0)
    {
        /* Handle insertion when the list is empty. */
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        /* Handle insertion when the list is not empty */
        new_element->next = element;
        new_element->prev = element->prev;

        if (element->prev == NULL)
        {
            list->head = new_element;
        }
        else
        {
            element->prev->next = new_element;
        }
        element->prev = new_element;
    }

    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    /* Do not allow a NULL element or removal from an empty list. */
    if ((element == NULL) || (dlist_size(list) == 0))
    {
        return -1;
    }

    /* Remove the element from the list. */
    *data = element->data;

    if (element == list->head)
    {
        /* Handle removal from the head of the list. */
        list->head = element->next;

        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        else
        {
            element->next->prev = NULL;
        }
    }
    else
    {
        /* Handle removal from other than the haed of the list. */
        element->prev->next = element->next;
        if (element->next == NULL)
        {
            list->tail = element->prev;
        }
        else
        {
            element->next->prev = element->prev;
        }
    }

    /* Free the storage allocated for the element. */
    free(element);

    list->size--;
    return 0;
}

int dlist_find_elmt(DList *list, DListElmt **element, const void *data)
{
    if ((0 == dlist_size(list)) || (NULL == list->compare))
    {
        return -1;
    }

    DListElmt *current = dlist_head(list);
    while (NULL != current)
    {
        if (0 == list->compare(current->data, data))
        {
            *element = current;
            return 0;
        }
        current = current->next;
    }

    /* Didn't find the element with specific data. */
    return -1;
}
