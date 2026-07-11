#include "../include/date.hpp"


Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

long Date::daysInMonth(int month, int year) {
    if (month == 2 && isLeapYear(year))
        return 29;
    // month - 1 cause array start from 0
    return monthDays[month - 1];
}
long Date::toDayCount() const
{
    long total = 0;
    for (int y = 0; y < year; y++)
        total += (isLeapYear(y)) ? 366 : 365;
    for (int m = 1; m < month; m++)
        total += daysInMonth(m, year);
    total += day;
    return total;
}

Date Date::fromDayCount(long totalDays)
{
    int year = 0;
    while (true) {
        long daysThisYear = isLeapYear(year) ? 366 : 365;
        if (totalDays <= daysThisYear) break;
        totalDays -= daysThisYear;
        year++;
    }

    int month = 1;
    while (true) {
        long daysThisMonth = daysInMonth(month, year);
        if (totalDays <= daysThisMonth) break;
        totalDays -= daysThisMonth;
        month++;
    }

    int day = totalDays;

    return Date(day, month, year);
}

bool Date::operator<(const Date& other) const
{
    return toDayCount() < other.toDayCount();
}

bool Date::operator<=(const Date& other) const
{
    return toDayCount() <= other.toDayCount();
}

bool Date::operator>(const Date& other) const
{
    return toDayCount() > other.toDayCount();
}

bool Date::operator>=(const Date& other) const
{
    return toDayCount() >= other.toDayCount();
}

bool Date::operator==(const Date& other) const
{
    return toDayCount() == other.toDayCount();
}

bool Date::operator!=(const Date& other) const
{
    return toDayCount() != other.toDayCount();
}

Date Date::operator+(int daysToAdd) const
{
    return fromDayCount(toDayCount() + daysToAdd);
}

Date Date::operator-(int daysToSubtract) const
{
    return fromDayCount(toDayCount() - daysToSubtract);
}

long Date::operator-(const Date& other) const
{
    return toDayCount() - other.toDayCount();
}
std::ostream &operator<<(std::ostream &os, const Date &d)
{
    os << (d.day < 10 ? "0" : "") << d.day << "/"
       << (d.month < 10 ? "0" : "") << d.month << "/"
       << d.year;
    return os;
}

bool Date::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::CalculateLeapYears(int year1, int year2)
{
    int leapYears = 0;
    for (int year = year1; year <= year2; ++year)
    {
        if (isLeapYear(year))
        {
            leapYears++;
        }
    }
    return leapYears;
}

int Date::CalculateDays(Date date)
{
    int days = (date.year - 1950) * 365 + date.day;
    if(date.month > 2 && isLeapYear(date.year))
    {
        days++;
    }
    for(int i = 0; i < date.month - 1; i++)
    {
        days += monthDays[i];
    }
    days += CalculateLeapYears(1950, date.year - 1);
    return days;
}

int Date::daysSinceDeadline(Date endOfTermDate)
{

    //Check if student returned the book before the end of term date
    if( this->year < endOfTermDate.year
    || (this->year == endOfTermDate.year && this->month < endOfTermDate.month)
    || (this->year == endOfTermDate.year && this->month == endOfTermDate.month && this->day <= endOfTermDate.day))
    {
        return 0;
    }

    //Preparing days of each month
    int DayPasses = 0;

    return CalculateDays(*this) - CalculateDays(endOfTermDate);
    // with operators overloading implemented, this function can be one-line as below
    // abstraction absolute over-engineering 
    return (*this > endOfTermDate) ? (*this - endOfTermDate) : 0;
}   