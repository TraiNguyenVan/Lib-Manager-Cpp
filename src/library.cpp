#include "library.hpp"

// provide default value to assure safety
Library::Library(int id , string name)
{
    this->name = name;
    this->id = id;
}

bool Library::loadFromFile(const std::string &filepath)
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

Book Library::makeBookfromRecord(string ISBN, string title, string author, int available_copies)
{
    return Book(ISBN, title, author, available_copies);
}

string Library::makeRecord(Book &book)
{
    return book.getISBN() + "\n" + book.getTitle() + "\n" + book.getAuthor() + "\n" + to_string(book.getAvailableCopies());
}

bool Library::saveToFile(const std::string &filepath)
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