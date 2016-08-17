#include <string.h>
#include "traverse.h"

#include <queue>
using namespace std;


#include "gtest/gtest.h"

static BiTree tree;

class TraverseTest : public testing::Test {
protected:
    virtual void SetUp() {
        bitree_init(&tree, free);

        int *data = NULL;
        int a[] = {1, 2, 3, 4, 5, 6};
        unsigned int i = 0;
        unsigned int size = sizeof(a) / sizeof(a[0]);
        cout << "size: " << size << endl;
        data = (int*)malloc(sizeof(int));
        *data = a[i++];
        ASSERT_EQ(0, bitree_ins_left(&tree, NULL, data));

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
                data = (int*)malloc(sizeof(int));
                *data = a[i++];
                ASSERT_EQ(0, bitree_ins_left(&tree, node, data));
                q.push(node->left);
            }
            if (i != size)
            {
                data = (int*)malloc(sizeof(int));
                *data = a[i++];
                ASSERT_EQ(0, bitree_ins_right(&tree, node, data));
                q.push(node->right);
            }
        }
        cout << endl;

        int current = 0;
        int last = 1;
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

    virtual void TearDown() {
        bitree_destroy(&tree);
    }
};

TEST_F(TraverseTest, preorder) {
    List list;
    list_init(&list, NULL);
    ASSERT_EQ(0, list_size(&list));

    ASSERT_EQ(0, preorder(bitree_root(&tree), &list));
    ASSERT_EQ(bitree_size(&tree), list_size(&list));

    cout << "pre-order result: ";
    ListElmt* element = list_head(&list);
    while (NULL != element)
    {
        cout << *((int*)element->data) << " ";
        element = element->next;
    }
    cout << endl;
    list_destroy(&list);
}

TEST_F(TraverseTest, inorder) {
    List list;
    list_init(&list, NULL);
    ASSERT_EQ(0, list_size(&list));

    ASSERT_EQ(0, inorder(bitree_root(&tree), &list));
    ASSERT_EQ(bitree_size(&tree), list_size(&list));

    cout << "in-order result: ";
    ListElmt* element = list_head(&list);
    while (NULL != element)
    {
        cout << *((int*)element->data) << " ";
        element = element->next;
    }
    cout << endl;
    list_destroy(&list);
}

TEST_F(TraverseTest, postorder) {
    List list;
    list_init(&list, NULL);
    ASSERT_EQ(0, list_size(&list));

    ASSERT_EQ(0, postorder(bitree_root(&tree), &list));
    ASSERT_EQ(bitree_size(&tree), list_size(&list));

    cout << "post-order result: ";
    ListElmt* element = list_head(&list);
    while (NULL != element)
    {
        cout << *((int*)element->data) << " ";
        element = element->next;
    }
    cout << endl;
    list_destroy(&list);
}
