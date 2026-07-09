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

int Date::daysSinceDeadline(Date endOfTermDate, Date returnDate)
{

    //Check if student returned the book before the end of term date
    if( returnDate.year < endOfTermDate.year
    || (returnDate.year == endOfTermDate.year && returnDate.month < endOfTermDate.month)
    || (returnDate.year == endOfTermDate.year && returnDate.month == endOfTermDate.month && returnDate.day <= endOfTermDate.day))
    {
        return 0;
    }

    //Preparing days of each month
    int DayPasses = 0;
    int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    //Calculating part
    //Calculating difference in years
    if (endOfTermDate.year > returnDate.year)
    {
        if (endOfTermDate.year - returnDate.year != 1){
            for(int i = returnDate.year + 1; i < endOfTermDate.year; i++)
            {
                DayPasses += isLeapYear(i)? 366 : 365;
            }
        }
        for(int i = 1; i < returnDate.month; i++)
        {
            DayPasses += monthDays[i];
        }
        if (isLeapYear(returnDate.year) && returnDate.month > 2)
        {
            DayPasses += 1;
        }


        DayPasses += returnDate.day;
        returnDate.year = endOfTermDate.year;
        returnDate.month = 12; returnDate.day = 31;
    }
    //Calculating when no year different
    if(endOfTermDate.month == returnDate.month
    && endOfTermDate.day == returnDate.day)
    {
        return DayPasses;
    }
    for(int i = endOfTermDate.month++; i < returnDate.month--; i++)
    {
        DayPasses += monthDays[i - 1];
    }
    if (isLeapYear(returnDate.year)
    && returnDate.month > 2
    && (endOfTermDate.month < 2 || (endOfTermDate.month == 2 && endOfTermDate.day < 29)))
    {
        DayPasses += 1;
    }
    DayPasses += returnDate.day - endOfTermDate.day;
    return DayPasses;
}   