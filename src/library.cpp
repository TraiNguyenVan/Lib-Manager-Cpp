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
{
    ifstream fi(filepath);
    if (!fi.is_open())
        return false;

    int n;
    if (!(fi >> n))
        return false;
    fi.ignore();

    for (int i = 0; i < n; i++)
    {
        string ISBN, title, author;
        int available_copies;
        if (!getline(fi, ISBN) || !getline(fi, title) || !getline(fi, author) || !(fi >> available_copies))
            return false;
        fi.ignore();
        addBook(makeBookfromRecord(ISBN, title, author, available_copies));
    }
    return true;
};

Book Library::makeBookfromRecord(string ISBN, string title, string author, int available_copies)
{
    return Book(ISBN, title, author, available_copies);
}

// this one makes one record means one book
string Library::makeRecord(Book &book)
{
    return book.getISBN() + "\n" + book.getTitle() + "\n" + book.getAuthor() + "\n" + to_string(book.getAvailableCopies());
}


// this one simply makes mulitple records at once as a vector
vector<string> Library::makeRecords() {
    vector<string> records;
    for (auto it : Books)
    {
        Book book = it.second;
        records.push_back(makeRecord(book));
    }
    return records;
}

bool Library::saveToFile(const std::string &filepath)
{
    ofstream fo(filepath);
    vector<string> records = makeRecords();
    for (int i = 0; i < records.size(); ++i) {
        fo << records[i] << "\n";
    }
        return true;
}