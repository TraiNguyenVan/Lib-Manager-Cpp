#include <iostream>
#include "library.hpp"

using namespace std;

int main()
{

    const string database = "database.txt";
    Library Lib1(1, "Library");
    // Book book1("12345432345", "Game of Thrones", "Steve Jobs", 100);
    // InsertionStatus status = Lib1.addBook(book1);
    // switch (status)
    // {
    // case InsertionStatus::Success:
    //     cout << "Book inserted successfully!\n";
    //     break;
    // default:
    //     cout << "Unknow error\n";
    //     break;
    // }
    Lib1.loadFromFile(database);
    Lib1.saveToFile(database);

    return 0;
}