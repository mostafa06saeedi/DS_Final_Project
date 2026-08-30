#ifndef MAINTENANCE_USER_H
#define MAINTENANCE_USER_H

#include "User.h"

class Car;

class MaintenanceUser : public User
{
private:
    int completedRepairs = 0;
    double totalRepairCost = 0.0;

public:
    MaintenanceUser(const std::string &name,
                    const std::string &userName,
                    const std::string &password);

    virtual ~MaintenanceUser();

    bool scheduleMaintenance(Car *car, const std::string &description, double cost);
    bool completeMaintenance(int carId);

    int getCompletedRepairs() const { return completedRepairs; }
    double getTotalRepairCost() const { return totalRepairCost; }

    void commands() override;
};

#endif
