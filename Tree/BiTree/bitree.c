/* bitree.c */

#include <stdlib.h>
#include <string.h>

#include "bitree.h"

void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    /* Initialize the binary tree. */
    tree->size = 0;
    tree->root = NULL;
    tree->destroy = destroy;
}

void bitree_destory(BiTree *tree)
{
    /* Remove all the node from the tree. */
    bitree_rem_left(tree, NULL);

    /* No operations are allowed now. */
    memset(tree, 0, sizeof(BiTree));
    return;
}

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;

    /* Determine where to insert the node. */
    if (NULL == node)
    {
        /* Allow insertion at the root only in an empty tree. */
        if (!bitree_is_empty(tree))
        {
            return -1;
        }
        position = &tree->root;
    }
    else
    {
        /* Normally allow insertion only at the end of a branch. */
        if (bitree_left(node) != NULL)
        {
            return -1;
        }
        position = &node->left;
    }

    /* Allocate storage for the node. */
    new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    if (NULL == new_node)
    {
        return -1;
    }

    /* Insert the node into the tree. */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
    BiTreeNode *new_node, **position;

    /* Determine where to insert the node. */
    if (NULL == node)
    {
        /* Allow insertion at the root only in an empty tree. */
        if (!bitree_is_empty(tree))
        {
            return -1;
        }
        position = &tree->root;
    }
    else
    {
        /* Normally allow insertion only at the end of a branch. */
        if (bitree_right(node) != NULL)
        {
            return -1;
        }
        position = &node->right;
    }

    /* Allocate storage for the node. */
    new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    if (NULL == new_node)
    {
        return -1;
    }

    /* Insert the node into the tree. */
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
}
