#include <string.h>
#include "list.h"


#include "gtest/gtest.h"


TEST(Test_list_size, eqZero) {
    List list;
    list_init(&list, NULL, NULL);
    ASSERT_EQ(0, list_size(&list));
}

TEST(Test_list_size, eqOne) {
    List list;
    int data = 5;
    list_init(&list, NULL, NULL);
    list_ins_next(&list, NULL, &data);
    ASSERT_EQ(1, list_size(&list));
}


TEST(Test_list_is_empty, True) {
    List list;
    list_init(&list, NULL, NULL);
    ASSERT_EQ(true, list_is_empty(&list));
}

TEST(Test_list_is_empty, False) {
    List list;
    int data = 5;
    list_init(&list, NULL, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, NULL, &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));
}

TEST(Test_list_ins_next, Head) {
    List list;
    int data = 5;
    list_init(&list, NULL, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, list_head(&list), &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));
}

TEST(Test_list_ins_next, Tail) {
    List list;
    int data = 5;
    list_init(&list, NULL, NULL);
    list_ins_next(&list, NULL, &data);
    list_ins_next(&list, list_tail(&list), &data);
    ASSERT_EQ(2, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));
}

TEST(Test_list_rm_next, Head) {
    List list;
    int data = 5;
    list_init(&list, NULL, NULL);
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
    list_init(&list, NULL, NULL);
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
    list_init(&list, NULL, NULL);
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
    list_init(&list, destroy, NULL);
    list_ins_next(&list, NULL, student);
    ASSERT_EQ(1, list_size(&list));
    ASSERT_EQ(false, list_is_empty(&list));

    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}

TEST(Test_list_find_elmt, FailedSizeZero) {
    List list;
    Student *student = (Student *)malloc(sizeof(Student));
    strcpy(student->name, "eyotang");
    student->age = 15;
    list_init(&list, destroy, NULL);

    ListElmt *element = NULL;
    int ret = list_find_elmt(&list, &element, student);
    ASSERT_EQ(-1, ret);
    ASSERT_EQ(NULL, element);

    destroy(student);
    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}

TEST(Test_list_find_elmt, CompareNULL) {
    List list;
    Student *student = (Student *)malloc(sizeof(Student));
    strcpy(student->name, "eyotang");
    student->age = 15;
    list_init(&list, destroy, NULL);
    list_ins_next(&list, NULL, student);

    ListElmt *element = NULL;
    int ret = list_find_elmt(&list, &element, student);
    ASSERT_EQ(-1, ret);
    ASSERT_EQ(NULL, element);

    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}

static int compare(const void *key1, const void *key2)
{
    Student *student1 = (Student *)key1;
    Student *student2 = (Student *)key2;
    return strcmp(student1->name, student2->name);
}

TEST(Test_list_find_elmt, FailedWithoutResult) {
    List list;
    Student *student = (Student *)malloc(sizeof(Student));
    strcpy(student->name, "eyotang");
    student->age = 15;
    list_init(&list, destroy, compare);
    list_ins_next(&list, NULL, student);

    Student *student2 = (Student *)malloc(sizeof(Student));
    strcpy(student2->name, "eabcdef");
    student2->age = 15;

    ListElmt *element = NULL;
    int ret = list_find_elmt(&list, &element, student2);
    ASSERT_EQ(-1, ret);
    ASSERT_EQ(NULL, element);

    destroy(student2);
    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}

TEST(Test_list_find_elmt, SuccessWithResult) {
    List list;
    list_init(&list, destroy, compare);

    Student *student1 = (Student *)malloc(sizeof(Student));
    strcpy(student1->name, "eyotang");
    student1->age = 15;
    list_ins_next(&list, list_tail(&list), student1);

    Student *student2 = (Student *)malloc(sizeof(Student));
    strcpy(student2->name, "eabcdef");
    student2->age = 15;
    list_ins_next(&list, list_tail(&list), student2);

    ListElmt *element = NULL;
    int ret = list_find_elmt(&list, &element, student2);
    ASSERT_EQ(0, ret);
    ASSERT_NE((ListElmt *)NULL, element);
    ASSERT_EQ(student2, element->data);
    ASSERT_EQ(0, compare(student2, element->data));

    list_destroy(&list);
    ASSERT_EQ(true, list_is_empty(&list));
}
