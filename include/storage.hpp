#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <fstream>
using namespace std;

class Storage
{
public:
    // File operations on Books
    bool loadBooks(const std::string &filepath);
    bool saveBooks(const std::string &filepath);

    // Some ultilities for the saving process
    Book makeBookfromRecord(string ISBN, string title, string author, int available_copies);
    string makeRecord(Book &book);
    vector<string> makeRecords();

    // File operations Students
    bool loadStudents(const std::string &filepath);
    bool saveStudents(const std::string &filepath);
};

#endif