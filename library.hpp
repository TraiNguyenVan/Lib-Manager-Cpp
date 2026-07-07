#include <string>
#include <unordered_map>
#include <vector>
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
    Library(int id, string name, string filepath)
    {
        this->name = name;
        this->id = id;
    }
    InsertionStatus addBook(const Book &book) {
        this->Books.insert_or_assign(book.getISBN(), book);
        return InsertionStatus::Success;
    }
    CheckoutStatus checkOutBook(const std::string &id, const std::string &ISBN);
    bool returnBook(const std::string &id, const std::string &ISBN);
    std::vector<Book> searchBooks(std::string_view query) const;
    bool loadFromFile(const std::string &filepath)
    {
        return true;
    };
    bool saveToFile(const std::string &filepath) {

    }
    

private:
    int id;
    string name;
    unordered_map<string, Book> Books;
    unordered_map<string, Student> Students;
    vector<Transaction> transactions;
};
