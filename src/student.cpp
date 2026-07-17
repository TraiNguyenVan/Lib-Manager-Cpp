#include "../include/student.hpp"

Student::Student(string id, string name, string phone, int borrowedBooks,
                 vector<string> borrowedBookISBNs)
    : id(id),
      name(name),
      phone(phone),
      borrowedBooks(borrowedBooks),
      borrowedBookISBNs(borrowedBookISBNs) {}
