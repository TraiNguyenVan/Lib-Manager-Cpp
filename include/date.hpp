#ifndef DATE_HPP
#define DATE_HPP

#include <ostream>
#include <string>

using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;


    static constexpr int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static long daysInMonth(int month, int year);
    
    long toDayCount() const;
    static Date fromDayCount(long totalDays);


    static bool isLeapYear(int year);
    int CalculateLeapYears(int year1, int year2);
    int CalculateDays(Date date);
    //Calculating by transforming the date into days (from 1950 to date calculating date)

public:
    Date(int day, int month, int year);
    //Calculating how many days have passed since the end of term date
    int daysSinceDeadline(Date endOfTermDate);
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator>(const Date &other) const;
    bool operator<=(const Date &other) const;
    bool operator>=(const Date &other) const;
    Date operator+(int daysToAdd) const;
    Date operator-(int daysToSubtract) const;
    long operator-(const Date &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Date &d);

    // bool operator
};

#endif