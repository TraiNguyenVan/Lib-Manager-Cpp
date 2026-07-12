#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include <string>
#include <string_view>
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>
#include "student.hpp"
#include "book.hpp"
#include "transaction.hpp"

using namespace std;

enum class CheckoutStatus
{
    Success,
    BookNotFound,
    UserNotFound,
    OutOfStock,
    UserLimitReached,
    UserHasOverdueFines
};

enum class InsertionStatus
{
    Success,
    DuplicateISBN,
    InvalidData
};

class Library
{
public:
    // constructor
    Library(int id, string name);

    // Book's operations
    InsertionStatus addBook(const Book &book);
    CheckoutStatus checkOutBook(const std::string &id, const std::string &ISBN);
    bool returnBook(const std::string &id, const std::string &ISBN);

    std::vector<Book> searchBooks(std::string_view query) const;

    bool loadBooks(const std::string &filepath);
    bool saveBooks(const std::string &filepath);

    // Some ultilities for the saving process
    Book makeBookfromRecord(string ISBN, string title, string author, int available_copies);
    string makeRecord(Book &book);
    vector<string> makeRecords();

    // Student's operations
    bool loadStudents(const std::string &filepath);
    bool saveStudents(const std::string &filepath);

private:
    int id;
    string name;
    // Books with ISBN code as their index
    unordered_map<string, Book> Books;

    vector<Transaction> transactions;

    //The IDList have format as ID:Student info while ClassList have format as NameClass:ID Student.
    map<string, Student> IDList;
    map<string, vector<string>> ClassList;
};
#endif
