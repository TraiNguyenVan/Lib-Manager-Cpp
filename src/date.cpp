#include "../include/date.hpp"


Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
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
}   