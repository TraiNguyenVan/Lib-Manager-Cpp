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
    int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    //Calculating by transforming the date into days (from 1950 to return date)
    int days1 = (this->year - 1950) * 365 + this->day;
    if(this->month > 2 && isLeapYear(this->year))
    {
        days1++;
    }
    for(int i = 0; i < this->month - 1; i++)
    {
        days1 += monthDays[i];
    }
    days1 += CalculateLeapYears(1950, this->year - 1);

    //Now calculating from 1950 to end of term date)
    int days2 = (endOfTermDate.year - 1950) * 365 + endOfTermDate.day;
    if(endOfTermDate.month > 2 && isLeapYear(endOfTermDate.year))
    {
        days2++;
    }
    for(int i = 0; i < endOfTermDate.month - 1; i++)
    {
        days2 += monthDays[i];
    }
    days2 += CalculateLeapYears(1950, endOfTermDate.year - 1);
    return days1- days2;
}   