#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

using namespace std;

class Book
{
public:
    Book(string ISBN, string title, string author, int total_copies)
    {
        this->title = title;
        this->ISBN = ISBN;
        this->author = author;
        this->available_copies = total_copies;
    }
    string getISBN() const
    {
        return this->ISBN;
    }
    string getTitle() const
    {
        return this->title;
    }
    string getAuthor() const
    {
        return this->author;
    }
    int getAvailableCopies() const
    {
        return this->available_copies;
    }

private:
    string ISBN;
    string title;
    string author;
    int available_copies;
};
#endif