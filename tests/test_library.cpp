// this file now include both students and books tests, i was intended to make 2 seperated source
// files or something like that but i had no idea at the time so if your are readint this please
// improve it to be more modular

#include <gtest/gtest.h>

#include <cstdio>

#include "library.hpp"

TEST(LibraryTest, AddBook) {
    Library lib(1, "Test Library");
    Book book("9780307277671", "The Catcher in the Rye", "J.D. Salinger", 80);
    InsertionStatus status = lib.addBook(book);
    EXPECT_EQ(status, InsertionStatus::Success);
}

TEST(LibraryTest, LoadBooks) {
    Library lib(1, "Test Library");
    bool ok = lib.loadBooks(TEST_DATA_DIR "/books-data.txt");
    EXPECT_TRUE(ok);

    std::string tempPath = "lib_manager_test_load_books.txt";
    bool saved = lib.saveBooks(tempPath);
    EXPECT_TRUE(saved);

    std::ifstream fi(tempPath);
    ASSERT_TRUE(fi.is_open());
    int n = 0;
    fi >> n;
    EXPECT_EQ(n, 10);
    fi.close();
    std::remove(tempPath.c_str());
}

TEST(LibraryTest, LoadStudents) {
    Library lib(1, "Test Library");
    bool ok = lib.loadStudents(TEST_DATA_DIR "/student-data.txt");
    EXPECT_TRUE(ok);

    ASSERT_EQ(lib.ClassList.size(), 1);
    EXPECT_EQ(lib.ClassList.count("E25CQCE02-N"), 1);
    auto students = lib.ClassList["E25CQCE02-N"];
    ASSERT_EQ(students.size(), 3);
    EXPECT_EQ(students[0], "N25DECE086");
    EXPECT_EQ(students[1], "N25DECE085");
    EXPECT_EQ(students[2], "N25DECE036");
}

TEST(LibraryTest, SaveBooks) {
    Library lib(1, "Test Library");
    lib.addBook(Book("9780307277671", "The Catcher in the Rye", "J.D. Salinger", 80));
    lib.addBook(Book("9780451524935", "1984", "George Orwell", 75));

    bool saved = lib.saveBooks("lib_manager_test_save.txt");
    EXPECT_TRUE(saved);

    std::ifstream fi("lib_manager_test_save.txt");
    EXPECT_TRUE(fi.is_open());
    fi.close();
    std::remove("lib_manager_test_save.txt");
}

TEST(LibraryTest, LoadBooksInvalidPath) {
    Library lib(1, "Test Library");
    bool ok = lib.loadBooks("/nonexistent/path.txt");
    EXPECT_FALSE(ok);
}

TEST(LibraryTest, LoadStudentsInvalidPath) {
    Library lib(1, "Test Library");
    bool ok = lib.loadStudents("/nonexistent/path.txt");
    EXPECT_FALSE(ok);
}
