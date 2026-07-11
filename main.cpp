#include "include/library.hpp"
#include "include/date.hpp"
#include <iostream>

using namespace std;

void DateTest(){
    Date d1(1, 1, 2020);
    Date d2(1, 1, 2021);
    cout << "From 1/1/2020 to 1/1/2021 is " << d2.daysSinceDeadline(d1) << " days." << endl;
}

int main()
{
    DateTest();
    return 0;
}