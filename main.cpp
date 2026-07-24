#include <iostream>

#include "include/date.hpp"
#include "include/library.hpp"
#include "include/student.hpp"

using namespace std;

void DateTest() {
    Date d1(1, 1, 2020);
    Date d2(1, 1, 2021);
    cout << "From 1/1/2020 to 1/1/2021 is " << d2.daysSinceDeadline(d1) << " days." << endl;
}

void StudentInputTest() {
    Library lib(1, "Test Library");
    lib.loadStudents("./data/student-data.txt.example");
    // cout << "alo" << endl;
    for (const auto& it : lib.ClassList) {
        cout << "Class: " << it.first << ", Student IDs: ";
        for (const auto& studentID : it.second) {
            cout << studentID << " ";
        }
        cout << endl;
    }
}

int main() {
    DateTest();
    StudentInputTest();
    return 0;
}