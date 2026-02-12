#ifndef MAINTAIN_H
#define MAINTAIN_H

#include "Contract.h"
#include <string>

class Maintain : public Contract {
private:
    std::string description;
    size_t fee;

public:
    Maintain(Car* car,
             User* user,
             const Date& start,
             const Date& end,
             const std::string& description,
             size_t fee);

    const std::string& getDescription() const;
    size_t getFee() const;
};

#endif
