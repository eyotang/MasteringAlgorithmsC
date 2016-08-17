/* traverse.c */

#include "list.h"
#include "traverse.h"

/* pre-order */
int preorder(const BiTreeNode *node, List *list)
{
    /* Load the list with a preorder listing of the tree. */
    if (!bitree_is_eob(node))
    {
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        if (!bitree_is_eob(bitree_left(node)))
        {
            if (preorder(bitree_left(node), list) != 0)
                return -1;
        }
        if (!bitree_is_eob(bitree_right(node)))
        {
            if (preorder(bitree_right(node), list) != 0)
                return -1;
        }
    }

    return 0;
}

/* in-order */
int inorder(const BiTreeNode *node, List *list)
{
    /* Load the list with a inorder listing of the tree. */
    if (!bitree_is_eob(node))
    {
        if (!bitree_is_eob(bitree_left(node)))
        {
            if (inorder(bitree_left(node), list) != 0)
                return -1;
        }

        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;

        if (!bitree_is_eob(bitree_right(node)))
        {
            if (inorder(bitree_right(node), list) != 0)
                return -1;
        }
    }

    return 0;
}

/* post-order */
int postorder(const BiTreeNode *node, List *list)
{
    /* Load the list with a postorder listing of the tree. */
    if (!bitree_is_eob(node))
    {
        if (!bitree_is_eob(bitree_left(node)))
        {
            if (postorder(bitree_left(node), list) != 0)
                return -1;
        }

        if (!bitree_is_eob(bitree_right(node)))
        {
            if (postorder(bitree_right(node), list) != 0)
                return -1;
        }

        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0)
            return -1;
    }

    return 0;
}
