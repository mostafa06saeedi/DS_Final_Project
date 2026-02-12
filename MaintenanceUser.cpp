#include "MaintenanceUser.h"
#include "Car.h"
#include <iostream>

MaintenanceUser::MaintenanceUser(const std::string &name,
                                 const std::string &userName,
                                 const std::string &password)
    : User(name, userName, password, Status::Active)
{
}

MaintenanceUser::~MaintenanceUser()
{
}

bool MaintenanceUser::scheduleMaintenance(Car *car,
                                          const std::string &description,
                                          double cost)
{
    if (car == nullptr)
    {
        std::cout << "Invalid car.\n";
        return false;
    }

    if (cost < 0)
    {
        std::cout << "Cost cannot be negative.\n";
        return false;
    }

    car->scheduleMaintenance(description, cost);
    totalRepairCost += cost;

    std::cout << "Maintenance scheduled for Car #"
              << car->getCarId() << ".\n";

    return true;
}

bool MaintenanceUser::completeMaintenance(int carId)
{
    std::cout << "Maintenance completed for Car #"
              << carId << ".\n";

    completedRepairs++;
    return true;
}

void MaintenanceUser::commands()
{
    std::cout << "\nMaintenance User Menu\n";
    std::cout << "----------------------------------------\n";
    std::cout << "1. View cars needing maintenance\n";
    std::cout << "2. Start maintenance\n";
    std::cout << "3. Complete maintenance\n";
    std::cout << "4. View maintenance log\n";
    std::cout << "0. Exit\n";
}
