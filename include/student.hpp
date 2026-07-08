#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

using namespace std;

class Student
{
public:
    Student(int id, string name, string phone);

private:
    int id;
    string name;
    string phone;
};

#endif