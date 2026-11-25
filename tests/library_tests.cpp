#include "library.hpp"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

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

}  // namespace

int main(int argc, char *argv[]) {
    if (argc != 2) return 2;
    checkBookRoundTrip(argv[1]);
    checkEmptyCatalog();
    checkWriteFailure();
    return failures == 0 ? 0 : 1;
}
