#include "book.hpp"

Book::Book(string ISBN, string title, string author, int total_copies) {
    this->title = title;
    this->ISBN = ISBN;
    this->author = author;
    this->available_copies = total_copies;
}
string Book::getISBN() const { return this->ISBN; }
string Book::getTitle() const { return this->title; }
string Book::getAuthor() const { return this->author; }
int Book::getAvailableCopies() const { return this->available_copies; }