#include "Maintain.h"

Maintain::Maintain(Car* car,
                   User* user,
                   const Date& start,
                   const Date& end,
                   const std::string& desc,
                   size_t fee)
    : Contract(car, user, start, end, Type::Maintain),
      description(desc),
      fee(fee) {}

const std::string& Maintain::getDescription() const {
    return description;
}

size_t Maintain::getFee() const {
    return fee;
}