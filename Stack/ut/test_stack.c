#include <string.h>
#include "stack.h"

#include "gtest/gtest.h"


TEST(Test_stack_peek, NULL) {
    Stack stack;
    stack_init(&stack, NULL);
    ASSERT_EQ(NULL, stack_peek(&stack));
    stack_destroy(&stack);
}

TEST(Test_stack_peek, notNULL) {
    Stack stack;
    int data = 100;
    stack_init(&stack, NULL);
    stack_push(&stack, &data);
    ASSERT_EQ(data, *(int*)(stack_peek(&stack)));
    stack_destroy(&stack);
}

TEST(Test_stack_pop, NULL) {
    Stack stack;
    void *p = NULL;
    stack_init(&stack, NULL);
    stack_pop(&stack, &p);
    ASSERT_EQ(NULL, p);
    stack_destroy(&stack);
}

TEST(Test_stack_pop, notNULL) {
    Stack stack;
    int data = 100;
    int *p = NULL;
    stack_init(&stack, NULL);
    stack_push(&stack, &data);
    ASSERT_EQ(1, stack_size(&stack));

    stack_pop(&stack, (void **)&p);
    ASSERT_EQ(data, *p);
    stack_destroy(&stack);
}
