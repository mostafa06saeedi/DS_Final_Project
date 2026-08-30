#ifndef CONTRACT_H
#define CONTRACT_H
#include <cstddef>
#include <stdexcept>
#include "Date.h"

class Car;
class User;

class Contract
{
public:
    enum class Type
    {
        Rent,
        Reserve,
        Maintain,
        Extend
    };

private:
    const Car *const car;
    const User *const user;
    const Date startDate;
    Date endDate;
    Type type;
    bool active;

public:
    Contract(Car *car,
             User *user,
             const Date &start,
             const Date &end,
             Type type);

    void expire();
    bool isActive() const;

    bool timeExtend(size_t days);
    bool changeType(Type newType);
    const Car *getCar() const;
    const User *getUser() const;
    const Date &getStartDate() const;
    const Date &getEndDate() const;
    const Date &getReturnDate() const { return endDate; }
    Type getType() const;
    long getDuration() const;

    std::string getCustomerId() const;
};

#endif