#include <gtest/gtest.h>

#include <sstream>

#include "../include/date.hpp"

TEST(DateTest, Constructor) {
    Date d(15, 3, 2024);
    EXPECT_EQ(d, d);
}

TEST(DateTest, Equality) {
    Date d1(1, 1, 2020);
    Date d2(1, 1, 2020);
    Date d3(2, 1, 2020);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
}

TEST(DateTest, Inequality) {
    Date d1(1, 1, 2020);
    Date d2(2, 1, 2020);
    EXPECT_TRUE(d1 != d2);
    EXPECT_FALSE(d1 != d1);
}

TEST(DateTest, LessThan) {
    Date d1(1, 1, 2020);
    Date d2(1, 2, 2020);
    Date d3(1, 1, 2021);
    Date d4(1, 1, 2020);
    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d1 < d3);
    EXPECT_FALSE(d2 < d1);
    EXPECT_FALSE(d1 < d4);
}

TEST(DateTest, GreaterThan) {
    Date d1(2, 1, 2020);
    Date d2(1, 1, 2020);
    Date d3(1, 1, 2020);
    EXPECT_TRUE(d1 > d2);
    EXPECT_FALSE(d2 > d1);
    EXPECT_FALSE(d1 > d1);
    EXPECT_TRUE(d1 > d3);
}

TEST(DateTest, LessOrEqual) {
    Date d1(1, 1, 2020);
    Date d2(2, 1, 2020);
    Date d3(1, 1, 2020);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 <= d3);
    EXPECT_FALSE(d2 <= d1);
}

TEST(DateTest, GreaterOrEqual) {
    Date d1(2, 1, 2020);
    Date d2(1, 1, 2020);
    Date d3(1, 1, 2020);
    EXPECT_TRUE(d1 >= d2);
    EXPECT_TRUE(d1 >= d3);
    EXPECT_FALSE(d2 >= d1);
}

TEST(DateTest, AddDays) {
    Date d(1, 1, 2020);
    EXPECT_EQ(d + 1, Date(2, 1, 2020));
}

TEST(DateTest, AddDaysCrossMonth) {
    Date d(31, 1, 2020);
    EXPECT_EQ(d + 1, Date(1, 2, 2020));
}

TEST(DateTest, AddDaysCrossYear) {
    Date d(31, 12, 2020);
    EXPECT_EQ(d + 1, Date(1, 1, 2021));
}

TEST(DateTest, AddDaysLeapYearFeb) {
    Date d(28, 2, 2020);
    EXPECT_EQ(d + 1, Date(29, 2, 2020));
}

TEST(DateTest, AddDaysNonLeapYearFeb) {
    Date d(28, 2, 2021);
    EXPECT_EQ(d + 1, Date(1, 3, 2021));
}

TEST(DateTest, SubtractDays) {
    Date d(2, 1, 2020);
    EXPECT_EQ(d - 1, Date(1, 1, 2020));
}

TEST(DateTest, SubtractDaysCrossMonth) {
    Date d(1, 3, 2020);
    EXPECT_EQ(d - 1, Date(29, 2, 2020));
}

TEST(DateTest, SubtractDaysCrossYear) {
    Date d(1, 1, 2021);
    EXPECT_EQ(d - 1, Date(31, 12, 2020));
}

TEST(DateTest, DaysBetween) {
    Date d1(1, 1, 2020);
    Date d2(1, 1, 2021);
    EXPECT_EQ(d2 - d1, 366);
}

TEST(DateTest, DaysBetweenSameDay) {
    Date d(1, 1, 2020);
    EXPECT_EQ(d - d, 0);
}

TEST(DateTest, DaysBetweenNonLeapYear) {
    Date d1(1, 1, 2021);
    Date d2(1, 1, 2022);
    EXPECT_EQ(d2 - d1, 365);
}

TEST(DateTest, DaysSinceDeadlineBefore) {
    Date deadline(1, 6, 2024);
    Date returned(15, 5, 2024);
    EXPECT_EQ(returned.daysSinceDeadline(deadline), 0);
}

TEST(DateTest, DaysSinceDeadlineOnDeadline) {
    Date deadline(1, 6, 2024);
    Date returned(1, 6, 2024);
    EXPECT_EQ(returned.daysSinceDeadline(deadline), 0);
}

TEST(DateTest, DaysSinceDeadlineAfter) {
    Date deadline(1, 6, 2024);
    Date returned(15, 6, 2024);
    EXPECT_GT(returned.daysSinceDeadline(deadline), 0);
}

TEST(DateTest, LeapYear2000) {
    Date feb28(28, 2, 2000);
    EXPECT_EQ(feb28 + 1, Date(29, 2, 2000));
}

TEST(DateTest, NonLeapYear1900) {
    Date feb28(28, 2, 1900);
    EXPECT_EQ(feb28 + 1, Date(1, 3, 1900));
}

TEST(DateTest, OutputStream) {
    Date d(5, 3, 2024);
    std::ostringstream os;
    os << d;
    EXPECT_EQ(os.str(), "05/03/2024");
}

TEST(DateTest, OutputStreamNoLeadingZero) {
    Date d(15, 11, 2024);
    std::ostringstream os;
    os << d;
    EXPECT_EQ(os.str(), "15/11/2024");
}
