#include "include/library.hpp"
#include <iostream>

using namespace std;

int main()
{
    Library TestLib(1, "Test Library");
    TestLib.loadStudents("data/students-data.txt");
    return 0;
}