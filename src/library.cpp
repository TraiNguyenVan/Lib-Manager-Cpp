#include "../include/library.hpp"
#define lib Library

#include <iostream>
using namespace std;

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

bool lib::loadBooks(const std::string &filepath)
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

bool Library::saveBooks(const std::string &filepath)
{
    ofstream fo(filepath);
    fo << Books.size() << "\n";
    vector<string> records = makeRecords();
    for (int i = 0; i < records.size(); ++i) {
        fo << records[i] << "\n";
    }
        return true;
}

bool Library::loadStudents(const std::string &filepath){
    ifstream fi(filepath);
    if (!fi.is_open()) return false;
    int n;
    if (!(fi >> n)) return false;
    fi.ignore();
    for(int i = 0; i < n; i++){
        string Tclass;
        getline(fi, Tclass); //fi.ignore();

        string name, Tid;
        int numStudents, borrowedBooks;
        vector<string> id;

        fi >> numStudents; fi.ignore();
        for(int j = 0; j < numStudents; j++){
            vector<string> ISBN;
            getline(fi, name);
            getline(fi, Tid);

            id.push_back(Tid);

            fi >> borrowedBooks; fi.ignore();
            for(int k = 0; k < borrowedBooks; k++){
                string temp;
                getline(fi, temp);
                ISBN.push_back(temp);
                // Add the borrowed book ISBN to the student's record
            }
            IDList.insert_or_assign(Tid, Student(Tid, name, "", borrowedBooks, ISBN));
        }

        ClassList[Tclass] = id;

    }
    return 1;
}