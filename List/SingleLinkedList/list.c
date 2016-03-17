/* list.c */

#include <stdlib.h>
#include <string.h>

#include "list.h"


void list_init(List *list, void (*destroy)(void *data), int (*compare)(const void *key1, const void *key2))
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
    new_element = (ListElmt *)malloc(sizeof(ListElmt));
    if (NULL == new_element)
    {
        return -1;
    }
    new_element->data = (void*)data;

    if (NULL == element)
    {
        if (0 == list_size(list))
        {
            list->tail = new_element;
        }
        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
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
    if (0 == list_size(list))
    {
        return -1;
    }

    if (NULL == element)
    {
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

    /**
     * Didn't find the element with specific data
     */
    return -1;
}
