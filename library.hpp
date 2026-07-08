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
    private:
        int id;
        string name;
        unordered_map<string, Book> Books;
        unordered_map<string, Student> Students;
        vector<Transaction> transactions;
    public:
        //Default assign value for Library
        Library(int id, string name);

        //
        InsertionStatus addBook(const Book &book);

        //Record the book being borrow?
        CheckoutStatus checkOutBook(const std::string &id, const std::string &ISBN);

        //Should add more information soon
        bool returnBook(const std::string &id, const std::string &ISBN);

        //
        std::vector<Book> searchBooks(std::string_view query) const;

        //Load book data from file into database? 
        bool loadFromFile(const std::string &filepath);
    
        //From text, turn them into "Book" type to load in databasez
        Book makeBookfromRecord(string ISBN, string title, string author, int available_copies)
        {
            return Book(ISBN, title, author, available_copies);
        }
        
        //
        string makeRecord(Book &book)
        {
            return book.getISBN() + "\n" + book.getTitle() + "\n" + book.getAuthor() + "\n" + to_string(book.getAvailableCopies());
        }
    
        //
        bool saveToFile(const std::string &filepath);
    
    
    };
#endif
