#ifndef DATE_H
#define DATE_H

#include <string>
#include <cstddef>
#include <stdexcept>
#include <sstream>

class Date
{
private:
    size_t day;
    size_t month;
    size_t year;

    static size_t daysInMonth(size_t month);

public:
    Date();
    Date(size_t day, size_t month, size_t year);

    bool isValid() const;

    void setDate(size_t day, size_t month, size_t year);

    size_t getDay() const;
    size_t getMonth() const;
    size_t getYear() const;

    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator>(const Date &other) const;
    bool operator<=(const Date &other) const;
    bool operator>=(const Date &other) const;

    long toAbsoluteDays() const;

    long daysBetween(const Date &other) const;

    std::string toString() const;
};

#endif
