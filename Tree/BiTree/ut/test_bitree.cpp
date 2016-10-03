#include <string.h>
#include "bitree.h"

#include <queue>
using namespace std;


#include "gtest/gtest.h"


TEST(Test_bitree_size, eqZero) {
    BiTree tree;
    bitree_init(&tree, NULL);
    ASSERT_EQ(0, bitree_size(&tree));
}

TEST(Test_bitree_build_tree, Success) {
    BiTree tree;
    bitree_init(&tree, NULL);

    int a[] = {1, 2, 3, 4, 5, 6};
    unsigned int i = 0;
    unsigned int size = sizeof(a) / sizeof(a[0]);
    cout << "size: " << size << endl;
    ASSERT_EQ(0, bitree_ins_left(&tree, NULL, &a[i]));
    i++;

    queue<BiTreeNode *> q;
    q.push(tree.root);

    BiTreeNode *node = NULL;
    while (!q.empty())
    {
        node = q.front();
        cout << *((int *)node->data) << " ";
        q.pop();
        if (i != size)
        {
            ASSERT_EQ(0, bitree_ins_left(&tree, node, &a[i]));
            q.push(node->left);
            i++;
        }
        if (i != size)
        {
            ASSERT_EQ(0, bitree_ins_right(&tree, node, &a[i]));
            q.push(node->right);
            i++;
        }
    }
    cout << endl;

    unsigned int current = 0;
    unsigned int last = 1;
    vector <BiTreeNode *> vec;
    vec.push_back(tree.root);

    while(current < vec.size())
    {
        last = vec.size();
        /* layer start */
        while(current < last)
        {
            node = vec[current];
            cout << *((int*)node->data) << " ";
            if (node->left != NULL) {
                vec.push_back(node->left);
            }
            if (node->right != NULL) {
                vec.push_back(node->right);
            }
            current++;
        }
        cout << endl;
    }
}
