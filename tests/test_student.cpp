#include <gtest/gtest.h>
#include "student.hpp"

TEST(StudentTest, ConstructorAndGetters) {
    Student student("N25DECE085", "Van Trai", "0123456789", 1, {"1234567"});
    EXPECT_EQ(student.getID(), "N25DECE085");
    EXPECT_EQ(student.getName(), "Van Trai");
}
