#include "Contract.h"
#include "Car.h"
#include "User.h"
#include <iostream>

Contract::Contract(Car *car,
                   User *user,
                   const Date &start,
                   const Date &end,
                   Type t)
    : car(car),
      user(user),
      startDate(start),
      endDate(end),
      type(t),
      active(true)
{
    if (!car || !user)
    {
        throw std::invalid_argument("Car or User cannot be null");
    }
    if (endDate < startDate)
    {
        throw std::invalid_argument("End date cannot be before start date");
    }
}

void Contract::expire()
{
    active = false;
}

bool Contract::isActive() const
{
    return active;
}

bool Contract::timeExtend(size_t days)
{
    if (!active)
        return false;
    return true;
}

bool Contract::changeType(Type newType)
{
    if (!active)
        return false;
    if (type == Type::Reserve && newType == Type::Rent)
    {
        type = newType;
        return true;
    }
    return false;
}

const Car *Contract::getCar() const
{
    return car;
}

const User *Contract::getUser() const
{
    return user;
}

const Date &Contract::getStartDate() const
{
    return startDate;
}

const Date &Contract::getEndDate() const
{
    return endDate;
}

Contract::Type Contract::getType() const
{
    return type;
}

long Contract::getDuration() const
{
    return endDate.daysBetween(startDate);
}

std::string Contract::getCustomerId() const
{
    return user ? user->getUserName() : "unknown";
}