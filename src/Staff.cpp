#include "Staff.h"
#include "Car.h"
#include "Customer.h"
#include "Config.h"
#include "Date.h"
#include <iostream>
#include <iomanip>

Staff::Staff(const std::string &name,
             const std::string &username,
             const std::string &password)
    : User(name, username, password, Status::Active),
      carCatalog(nullptr)
{
}

void Staff::setCarCatalog(DoublyLinkedList<Car *> *catalog)
{
    carCatalog = catalog;
}

bool Staff::addNewCar(int carId, const std::string &plate, const std::string &brand,
                      const std::string &model, double pricePerDay)
{
    if (!carCatalog)
    {
        std::cout << "Car catalog not available.\n";
        return false;
    }

    auto node = carCatalog->getHead();
    while (node)
    {
        if (node->data->getCarId() == carId)
        {
            std::cout << "Car with ID #" << carId << " already exists.\n";
            return false;
        }
        node = node->next;
    }

    if (plate.empty() || brand.empty() || model.empty())
    {
        std::cout << "Car details cannot be empty.\n";
        return false;
    }

    if (pricePerDay <= 0)
    {
        std::cout << "Price per day must be greater than 0.\n";
        return false;
    }

    Car *newCar = new Car(carId, plate, brand, model, pricePerDay);
    carCatalog->insertBack(newCar);

    std::cout << "Car added successfully!\n";
    std::cout << "ID: " << carId << " | " << brand << " " << model << "\n";
    std::cout << "Plate: " << plate << " | Price: $" << pricePerDay << "/day\n";

    return true;
}

bool Staff::convertReservationToRental(int carId, Customer *customer)
{
    if (!carCatalog)
    {
        std::cout << "Car list not available.\n";
        return false;
    }

    if (!customer)
    {
        std::cout << "Customer not found.\n";
        return false;
    }

    auto node = carCatalog->getHead();
    Car *targetCar = nullptr;

    while (node)
    {
        if (node->data->getCarId() == carId)
        {
            targetCar = node->data;
            break;
        }
        node = node->next;
    }

    if (!targetCar)
    {
        std::cout << "Car #" << carId << " not found.\n";
        return false;
    }

    Contract *contract = targetCar->startRental();
    if (contract)
    {
        customer->moveReservationToActive(contract);
        std::cout << "Reservation converted to active rental for Car #"
                  << carId << ".\n";
        return true;
    }

    std::cout << "Unable to convert reservation to rental.\n";
    return false;
}

bool Staff::processReturn(int carId, const Date &actualReturnDate)
{
    if (!carCatalog)
    {
        std::cout << "Car list not available.\n";
        return false;
    }

    auto node = carCatalog->getHead();
    Car *targetCar = nullptr;

    while (node)
    {
        if (node->data->getCarId() == carId)
        {
            targetCar = node->data;
            break;
        }
        node = node->next;
    }

    if (!targetCar)
    {
        std::cout << "Car #" << carId << " not found.\n";
        return false;
    }

    std::cout << "Return registered for Car #" << carId << ".\n";

    Date expectedReturnDate = targetCar->getExpectedReturnDate();
    long lateDays = actualReturnDate.daysBetween(expectedReturnDate);

    if (lateDays > 0)
    {
        double dailyRate = targetCar->getPricePerDay();
        double penalty =
            dailyRate * Config::DAILY_PENALTY_RATE * lateDays;

        std::cout << "Late return penalty: "
                  << std::fixed << std::setprecision(2)
                  << penalty << " ("
                  << lateDays << " days late)\n";
    }
    else if (lateDays == 0)
    {
        std::cout << "Returned on time. No penalty.\n";
    }
    else
    {
        std::cout << "Returned early. No penalty.\n";
    }

    targetCar->completeRental();
    return true;
}

bool Staff::scheduleMaintenance(int carId,
                                const std::string &desc,
                                double cost)
{
    if (!carCatalog)
    {
        std::cout << "Car list not available.\n";
        return false;
    }

    auto node = carCatalog->getHead();
    Car *targetCar = nullptr;

    while (node)
    {
        if (node->data->getCarId() == carId)
        {
            targetCar = node->data;
            break;
        }
        node = node->next;
    }

    if (!targetCar)
    {
        std::cout << "Car #" << carId << " not found.\n";
        return false;
    }

    targetCar->scheduleMaintenance(desc, cost);

    std::cout << "Maintenance scheduled for Car #"
              << carId << ".\n";
    std::cout << "Description: " << desc << "\n";
    std::cout << "Cost: " << cost << "\n";

    return true;
}

bool Staff::completeMaintenance(int carId)
{
    if (!carCatalog)
    {
        std::cout << "Car list not available.\n";
        return false;
    }

    auto node = carCatalog->getHead();
    Car *targetCar = nullptr;

    while (node)
    {
        if (node->data->getCarId() == carId)
        {
            targetCar = node->data;
            break;
        }
        node = node->next;
    }

    if (!targetCar)
    {
        std::cout << "Car #" << carId << " not found.\n";
        return false;
    }

    targetCar->completeMaintenance();
    return true;
}

void Staff::commands()
{
    std::cout << "\nStaff Menu\n";
    std::cout << "----------------------------------------\n";
    std::cout << "1. Convert reservation to rental\n";
    std::cout << "2. Register car return\n";
    std::cout << "3. Schedule maintenance\n";
    std::cout << "4. View car status\n";
    std::cout << "5. Calculate penalty\n";
    std::cout << "0. Exit\n";
}
