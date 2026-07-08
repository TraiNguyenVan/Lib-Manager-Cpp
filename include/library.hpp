#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include <string>
#include <string_view>
#include <unordered_map>
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
    Library(int id, string name);
    InsertionStatus addBook(const Book &book)
    {
        this->Books.insert_or_assign(book.getISBN(), book);
        return InsertionStatus::Success;
    }
    CheckoutStatus checkOutBook(const std::string &id, const std::string &ISBN);
    bool returnBook(const std::string &id, const std::string &ISBN);
    std::vector<Book> searchBooks(std::string_view query) const;
    bool loadFromFile(const std::string &filepath);
    Book makeBookfromRecord(string ISBN, string title, string author, int available_copies);
    string makeRecord(Book &book);
    bool saveToFile(const std::string &filepath);

private:
    int id;
    string name;
    unordered_map<string, Book> Books;
    unordered_map<string, Student> Students;
    vector<Transaction> transactions;
};
#endif
