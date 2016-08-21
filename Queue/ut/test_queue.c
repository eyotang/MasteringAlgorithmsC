#include <string.h>
#include "queue.h"

#include "gtest/gtest.h"


TEST(Test_queue_push, success) {
    int data = 1;
    int *value = NULL;
    int result = -1;
    Queue queue;
    queue_init(&queue, NULL);
    result = queue_push(&queue, &data);
    ASSERT_EQ(0, result);
    ASSERT_EQ(1, queue_size(&queue));

    value = (int*)queue_front(&queue);
    ASSERT_EQ(1, *value);

    result = queue_pop(&queue, (void**)&value);
    ASSERT_EQ(0, result);
    ASSERT_EQ(1, *value);

    queue_destroy(&queue);
}
