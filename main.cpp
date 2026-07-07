#include <iostream>
#include "library.hpp"

using namespace std;

int main()
{

    const string filepath = "data.txt";
    Library Lib1(1, "Library", filepath);
    Book book1("12345432345", "Game of Thrones", "Steve Jobs", 100);
    InsertionStatus status = Lib1.addBook(book1);
    switch (status)
    {
    case InsertionStatus::Success:
        cout << "Book inserted successfully!\n";
        break;
    default:
        cout << "Unknow error\n";
        break;
    }
    
    // Lib1.saveToFile(filepath);

    return 0;
}