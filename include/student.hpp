#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "date.hpp"
#include <string>
#include <vector>

using namespace std;

class Student
{
private:
    string id;
    string name;
    string phone;
    int borrowedBooks;
    vector<string> borrowedBookISBNs;

    
public:
    Student(string id, string name, string phone, 
        int borrowedBooks, vector<string> borrowedBookISBNs);                                                                                                                                                                                                                       
    
    string getName() const {return name;}
    string getID() const {return id;}
};

#endif