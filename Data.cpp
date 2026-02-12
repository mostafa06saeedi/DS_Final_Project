#include "Date.h"
#include <sstream>
#include <iomanip>
#include <cmath>

Date::Date() : day(1), month(1), year(1404) {}

Date::Date(size_t d, size_t m, size_t y)
{
    setDate(d, m, y);
}

void Date::setDate(size_t d, size_t m, size_t y)
{
    day = d;
    month = m;
    year = y;
    if (!isValid())
    {
        throw std::invalid_argument("Invalid Shamsi date: " +
                                    std::to_string(y) + "/" +
                                    std::to_string(m) + "/" +
                                    std::to_string(d));
    }
}

bool Date::isValid() const
{
    if (year < 1 || year > 9999)
        return false;
    if (month < 1 || month > 12)
        return false;
    size_t maxDay = daysInMonth(month);
    return (day >= 1 && day <= maxDay);
}

long Date::toAbsoluteDays() const
{
    long totalDays = (year - 1) * 365L;

    long leapYears = ((year - 1) / 33) * 8;
    int remainder = (year - 1) % 33;
    if (remainder >= 30)
        leapYears += 8;
    else if (remainder >= 26)
        leapYears += 7;
    else if (remainder >= 22)
        leapYears += 6;
    else if (remainder >= 17)
        leapYears += 5;
    else if (remainder >= 13)
        leapYears += 4;
    else if (remainder >= 9)
        leapYears += 3;
    else if (remainder >= 5)
        leapYears += 2;
    else if (remainder >= 1)
        leapYears += 1;

    totalDays += leapYears;

    for (size_t m = 1; m < month; ++m)
    {
        totalDays += daysInMonth(m);
    }

    totalDays += day;

    return totalDays;
}

long Date::daysBetween(const Date &other) const
{
    return std::abs(toAbsoluteDays() - other.toAbsoluteDays());
}

bool Date::operator==(const Date &other) const
{
    return (year == other.year && month == other.month && day == other.day);
}

bool Date::operator!=(const Date &other) const
{
    return !(*this == other);
}

bool Date::operator<(const Date &other) const
{
    if (year != other.year)
        return year < other.year;
    if (month != other.month)
        return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date &other) const
{
    return other < *this;
}

bool Date::operator<=(const Date &other) const
{
    return !(*this > other);
}

bool Date::operator>=(const Date &other) const
{
    return !(*this < other);
}

std::string Date::toString() const
{
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << "/"
        << std::setw(2) << std::setfill('0') << month << "/"
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

size_t Date::daysInMonth(size_t month)
{
    if (month >= 1 && month <= 6)
        return 31;
    if (month >= 7 && month <= 11)
        return 30;
    if (month == 12)
        return 29;
    return 0;
}

size_t Date::getDay() const { return day; }
size_t Date::getMonth() const { return month; }
size_t Date::getYear() const { return year; }
