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
        Library(int id, string name)
        {
            this->name = name;
            this->id = id;
        }
        InsertionStatus addBook(const Book &book)
        {
            this->Books.insert_or_assign(book.getISBN(), book);
            return InsertionStatus::Success;
        }
        CheckoutStatus checkOutBook(const std::string &id, const std::string &ISBN);
        bool returnBook(const std::string &id, const std::string &ISBN);
        std::vector<Book> searchBooks(std::string_view query) const;
        bool loadFromFile(const std::string &filepath)
        {
            ifstream fi(filepath);
            int n;
            fi >> n;
            fi.ignore();
            for (int i = 0; i < n; i++)
            {
                string ISBN, title, author;
                int available_copies;
                getline(fi, ISBN);
                getline(fi, title);
                getline(fi, author);
                fi >> available_copies;
                fi.ignore();
                addBook(makeBookfromRecord(ISBN, title, author, available_copies));
            }
    
            return true;
        };
    
        Book makeBookfromRecord(string ISBN, string title, string author, int available_copies)
        {
            return Book(ISBN, title, author, available_copies);
        }
    
        string makeRecord(Book &book)
        {
            return book.getISBN() + "\n" + book.getTitle() + "\n" + book.getAuthor() + "\n" + to_string(book.getAvailableCopies());
        }
    
        bool saveToFile(const std::string &filepath)
        {
            ofstream fo(filepath);
            fo << Books.size() << "\n";
            for (auto it : Books)
            {
                Book book = it.second;
                fo << makeRecord(book) << "\n";
            }
            return true;
        }
    
    private:
        int id;
        string name;
        unordered_map<string, Book> Books;
        unordered_map<string, Student> Students;
        vector<Transaction> transactions;
    };
#endif
