/* list.c */

#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init_arg(List *list, int count, ...)
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

    list_init_impl(list, (void (*)(void*))destroy, (int (*)(const void*, const void*))compare);

}

void list_init_impl(List *list, void (*destroy)(void *data), int (*compare)(const void *key1, const void *key2))
{
    /* Initialize the list */
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    list->destroy = destroy;
    list->compare = compare;

    return;
}

void list_destroy(List *list)
{
    void *data = NULL;

    /* Remove each element */
    while (list_size(list) > 0)
    {
        if ((list_rm_next(list, NULL, (void **)&data) == 0) && (NULL != list->destroy))
        {
            list->destroy(data);
        }
    }

    memset(list, 0, sizeof(List));
    return;
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element = NULL;

    /* Allocate the storage for the element. */
    new_element = (ListElmt *)malloc(sizeof(ListElmt));
    if (NULL == new_element)
    {
        return -1;
    }
    new_element->data = (void*)data;

    /* Insert the element into the list. */
    if (NULL == element)
    {
        /* Handle the insertion at the head of the list. */
        if (0 == list_size(list))
        {
            list->tail = new_element;
        }
        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        /* Handle the insertion somewhere other than at the head. */
        if (NULL == element->next)
        {
            list->tail = new_element;
        }
        new_element->next = element->next;
        element->next = new_element;
    }

    list->size++;
    return 0;
}

int list_rm_next(List *list, ListElmt *element, void **data)
{
    ListElmt *old_element = NULL;

    /* Don't allow removal from an empty list. */
    if (0 == list_size(list))
    {
        return -1;
    }

    /* Remove the element from the list. */
    if (NULL == element)
    {
        /* Handle the removal from the head of the list. */
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1)
        {
            list->tail = NULL;
        }
    }
    else
    {
        /* Handle removal from somewhere other than the head. */
        if (NULL == element->next)
        {
            return -1;
        }

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (NULL == element->next)
        {
            list->tail = element;
        }
    }

    /* Free the storage alloocated for the element. */
    free(old_element);
    list->size--;

    return 0;
}

int list_find_elmt(List *list, ListElmt **element, const void *data)
{
    if ((0 == list_size(list)) || (NULL == list->compare))
    {
        return -1;
    }

    ListElmt *current = list_head(list);
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
