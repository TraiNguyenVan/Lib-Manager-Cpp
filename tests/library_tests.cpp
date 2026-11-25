#include "library.hpp"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace {

int failures = 0;

void check(bool passed, const char *message) {
    if (!passed) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

void checkBookRoundTrip(const std::string &samplePath) {
    const char *path = "catalog-roundtrip.test.txt";
    Library original(1, "Original");
    check(original.loadBooks(samplePath), "load the sample catalog");
    auto expected = original.makeRecords();
    check(expected.size() == 10, "the sample contains all ten books");
    check(original.saveBooks(path), "save a populated catalog");

    Library reloaded(2, "Reloaded");
    check(reloaded.loadBooks(path), "reload the catalog just saved");
    auto actual = reloaded.makeRecords();
    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    check(actual == expected, "save and reload preserve every book field");
    std::remove(path);
}

void checkEmptyCatalog() {
    const char *path = "catalog-empty.test.txt";
    Library empty(1, "Empty");
    check(empty.saveBooks(path), "save an empty catalog");
    Library reloaded(2, "Reloaded");
    check(reloaded.loadBooks(path), "reload an empty catalog");
    check(reloaded.makeRecords().empty(), "the empty catalog stays empty");
    std::remove(path);
}

void checkWriteFailure() {
    const char *file = "catalog-not-a-directory.test.txt";
    std::ofstream marker(file);
    check(static_cast<bool>(marker), "create a regular file for the failure check");
    marker.close();
    Library lib(1, "Test");
    check(!lib.saveBooks(std::string(file) + "/books.txt"),
          "return false when the output path cannot be opened");
    std::remove(file);
}

void checkDuplicateISBN() {
    Library lib(1, "Test");
    const Book original("100", "Original", "Author", 2);
    const Book duplicate("100", "Replacement", "Another author", 9);
    check(lib.addBook(original) == InsertionStatus::Success, "add the original ISBN");
    check(lib.addBook(duplicate) == InsertionStatus::DuplicateISBN, "reject a repeated ISBN");
    const auto records = lib.makeRecords();
    check(records.size() == 1 && records[0] == lib.makeRecord(original),
          "keep the original on duplicate insertion");
}

void checkDuplicateImport() {
    const char *path = "catalog-duplicate.test.txt";
    {
        std::ofstream file(path);
        file << "2\n101\nNew title\nAuthor\n1\n100\nDuplicate title\nAuthor\n1\n";
    }
    Library lib(1, "Test");
    const Book original("100", "Original", "Author", 2);
    lib.addBook(original);
    check(!lib.loadBooks(path), "reject a file containing an already cataloged ISBN");
    const auto records = lib.makeRecords();
    check(records.size() == 1 && records[0] == lib.makeRecord(original),
          "a rejected import does not replace or partially add books");

    {
        std::ofstream file(path);
        file << "2\n101\nFirst title\nAuthor\n1\n101\nSecond title\nAuthor\n1\n";
    }
    Library empty(2, "Empty");
    check(!empty.loadBooks(path), "reject a repeated ISBN within the same file");
    check(empty.makeRecords().empty(), "do not partially load a duplicate ISBN file");
    std::remove(path);
}

void checkStudentFixture(const std::string &samplePath) {
    Library lib(1, "Test");
    check(lib.loadStudents(samplePath), "load the synthetic student example");
    const std::map<std::string, std::vector<std::string>> expected{
        {"DEMO-A", {"DEMO001", "DEMO002"}},
        {"DEMO-B", {"DEMO003"}},
    };
    check(lib.ClassList == expected, "preserve each synthetic class and its student IDs");
}

}  // namespace

int main(int argc, char *argv[]) {
    if (argc != 3) return 2;
    checkBookRoundTrip(argv[1]);
    checkEmptyCatalog();
    checkWriteFailure();
    checkDuplicateISBN();
    checkDuplicateImport();
    checkStudentFixture(argv[2]);
    return failures == 0 ? 0 : 1;
}
