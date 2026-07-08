#include "library.hpp"
#define lib Library

lib::Library(int id, string name)
{
    this->name = name;
    this->id = id;
}

InsertionStatus lib::addBook(const Book &book)
    {
        this->Books.insert_or_assign(book.getISBN(), book);
        return InsertionStatus::Success;
    }

bool lib::loadFromFile(const std::string &filepath){
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
}

bool lib::saveToFile(const std::string &filepath)
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