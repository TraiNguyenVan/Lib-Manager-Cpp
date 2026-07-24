#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

using namespace std;

class Book {
   public:
    Book(string ISBN, string title, string author, int total_copies);
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    int getAvailableCopies() const;

   private:
    string ISBN;
    string title;
    string author;
    int available_copies;
};
#endif