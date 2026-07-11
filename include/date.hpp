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


    int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeapYear(int year);
    int CalculateLeapYears(int year1, int year2);
    int CalculateDays(Date date);

public:
    Date(int day, int month, int year);
    //Calculating how many days have passed since the end of term date
    int daysSinceDeadline(Date endOfTermDate);
};

#endif