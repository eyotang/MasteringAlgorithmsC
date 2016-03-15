#include "list.h"


#include "gtest/gtest.h"


TEST(Test_list_size, eqZero) {
    List list;
    list_init(&list, NULL);
    ASSERT_EQ(0, list_size(&list));
}

TEST(Test_list_size, eqOne) {
    List list;
    int data = 5;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data);
    ASSERT_EQ(1, list_size(&list));
}


TEST(Test_list_is_empty, True) {
    List list;
    list_init(&list, NULL);
    ASSERT_EQ(true, list_is_empty(&list));
}

TEST(Test_list_is_empty, False) {
    List list;
    int data = 5;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, NULL, &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));
}

TEST(Test_list_ins_next, Head) {
    List list;
    int data = 5;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, list_head(&list), &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));
}

TEST(Test_list_ins_next, Tail) {
    List list;
    int data = 5;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, list_tail(&list), &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));
}

TEST(Test_list_rm_next, Head) {
    List list;
    int data = 5;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, list_head(&list), &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));

    int *out = NULL;
    list_rm_next(&list, list_head(&list), (void **)&out);
    ASSERT_EQ(5, *out);
}

TEST(Test_list_rm_next, Data2) {
    List list;
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data3);
    list_ins_next(&list, NULL, &data2);
    list_ins_next(&list, NULL, &data1);
    ASSERT_EQ(3, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));

    int *out = NULL;
    list_rm_next(&list, list_head(&list), (void **)&out);
    ASSERT_EQ(data2, *out);
}


TEST(Test_list_destroy, Success) {
    List list;
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    list_init(&list, NULL);
    list_ins_next(&list, NULL, &data3);
    list_ins_next(&list, NULL, &data2);
    list_ins_next(&list, NULL, &data1);
    ASSERT_EQ(3, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));

    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}

typedef struct _Student
{
    char name[20];
    unsigned int age;
} Student;

static void destroy(void *data)
{
    Student *student = (Student *)data;
    if (NULL != student)
    {
        free(student);
        student = NULL;
    }
}

TEST(Test_list_destroy, NotNull) {
    List list;
    Student *student = (Student *)malloc(sizeof(Student));
    strcpy(student->name, "eyotang");
    student->age = 15;
    list_init(&list, destroy);
    list_ins_next(&list, NULL, student);
    ASSERT_EQ(1, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));

    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}
