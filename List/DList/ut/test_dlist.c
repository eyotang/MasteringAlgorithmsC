#include <string.h>
#include "dlist.h"


#include "gtest/gtest.h"


TEST(Test_dlist_size, eqZero) {
    DList list;
    dlist_init(&list, NULL);
    ASSERT_EQ(0, dlist_size(&list));
}
