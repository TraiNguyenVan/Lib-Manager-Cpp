#include <string>

using namespace std;

class Student
{
public:
    Student(int id, string name, string phone)
    {
        this->name = name;
        this->id = id;
        this->phone = phone;
    }

private:
    int id;
    string name;
    string phone;
};