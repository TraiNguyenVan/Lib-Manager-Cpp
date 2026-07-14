#include <gtest/gtest.h>
#include "book.hpp"

TEST(BookTest, ConstructorAndGetters) {
    Book book("9780307277671", "The Catcher in the Rye", "J.D. Salinger", 80);
    EXPECT_EQ(book.getISBN(), "9780307277671");
    EXPECT_EQ(book.getTitle(), "The Catcher in the Rye");
    EXPECT_EQ(book.getAuthor(), "J.D. Salinger");
    EXPECT_EQ(book.getAvailableCopies(), 80);
}
