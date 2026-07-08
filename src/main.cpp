#include <iostream>
#include "library.hpp"
#include <string>
#include <deque>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace std;

int main()
{

    const string database = "database.txt";
    Library Lib1(1, "Library");




    Lib1.loadFromFile(database);
    Lib1.saveToFile(database);

    return 0;
}