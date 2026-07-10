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

    //Calculating part
    //Calculating difference in years
    if (endOfTermDate.year > this->year)
    {
        if (endOfTermDate.year - this->year != 1){
            for(int i = this->year + 1; i < endOfTermDate.year; i++)
            {
                DayPasses += isLeapYear(i)? 366 : 365;
            }
        }
        for(int i = 1; i < this->month; i++)
        {
            DayPasses += monthDays[i];
        }
        if (isLeapYear(this->year) && this->month > 2)
        {
            DayPasses += 1;
        }


        DayPasses += this->day;
        this->year = endOfTermDate.year;
        this->month = 12; this->day = 31;
    }
    //Calculating when no year different
    if(endOfTermDate.month == this->month
    && endOfTermDate.day == this->day)
    {
        return DayPasses;
    }
    for(int i = endOfTermDate.month++; i < this->month--; i++)
    {
        DayPasses += monthDays[i - 1];
    }
    if (isLeapYear(this->year)
    && this->month > 2
    && (endOfTermDate.month < 2 || (endOfTermDate.month == 2 && endOfTermDate.day < 29)))
    {
        DayPasses += 1;
    }
    DayPasses += this->day - endOfTermDate.day;
    return DayPasses;
}   