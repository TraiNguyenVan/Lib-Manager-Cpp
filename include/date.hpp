#ifndef DATE_HPP
#define DATE_HPP

#include <string>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

    bool isLeapYear(int year);
    int CalculateLeapYears(int year1, int year2);

public:
    Date(int day, int month, int year);
    //Calculating how many days have passed since the end of term date
    int daysSinceDeadline(Date endOfTermDate);
};

#endif