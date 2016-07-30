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
    BiTreeNode **position;

    /* Do not allow removal from an empty tree. */
    if (bitree_is_empty(tree))
    {
        return;
    }

    /* Determine where to remove nodes. */
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->left;
    }

    /* Remove the nodes. */
    if (*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL)
        {
            /* Call a user-defined function to free dynamically allocated data. */
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        /* Adjust the size of the tree to account for the removed node. */
        tree->size--;
    }

    return;
}

void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;

    /* Do not allow removal from an empty tree. */
    if (bitree_is_empty(tree))
    {
        return;
    }

    /* Determine where to remove the nodes. */
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->right;
    }

    /* Remove the nodes. */
    if (*position != NULL)
    {
        bitree_rem_left(tree, *position);
        bitree_rem_right(tree, *position);

        if (tree->destroy != NULL)
        {
            /* Call a user-defined function to free dynamically allocated data. */
            tree->destroy((*position)->data);
        }

        free(*position);
        *position = NULL;

        /* Adjust the size of the tree to account for the removed node. */
        tree->size--;
    }

    return;
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
    return 0;
}
