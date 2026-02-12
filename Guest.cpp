#include "Guest.h"
#include "Car.h"
#include "DoublyLinkedList.h"
#include <iostream>

Guest::Guest(const std::string &name,
             const std::string &userName,
             const std::string &password)
    : User(name, userName, password, Status::Active) {}

Guest::~Guest() {}

void Guest::viewAllCars(const DoublyLinkedList<Car *> *carInventory) const
{
    if (!carInventory)
    {
        std::cout << "Car inventory not available.\n";
        return;
    }

    auto node = carInventory->getHead();
    if (!node)
    {
        std::cout << "No cars in the system.\n";
        return;
    }

    std::cout << "\nAvailable Cars:\n";
    std::cout << "----------------------------------------\n";

    int count = 0;

    while (node)
    {
        if (node->data &&
            node->data->getStatus() == Car::Status::Available)
        {
            std::cout << "ID: " << node->data->getCarId()
                      << " | " << node->data->getBrand()
                      << " " << node->data->getModel()
                      << " | Price: $" << node->data->getPricePerDay() << "/day"
                      << " | Plate: " << node->data->getLicensePlate()
                      << "\n";

            count++;
        }

        node = node->next;
    }

    if (count == 0)
    {
        std::cout << "No available cars at the moment.\n";
    }
    else
    {
        std::cout << "\nTotal available cars: " << count << "\n";
    }
}

Car *Guest::searchCarByBrand(const DoublyLinkedList<Car *> *carInventory,
                             const std::string &brand) const
{
    if (!carInventory)
    {
        std::cout << "Car inventory not available.\n";
        return nullptr;
    }

    auto node = carInventory->getHead();
    std::cout << "\nSearch results for brand: " << brand << "\n";
    std::cout << "----------------------------------------\n";

    int count = 0;

    while (node)
    {
        if (node->data &&
            node->data->getBrand() == brand &&
            node->data->getStatus() == Car::Status::Available)
        {
            std::cout << "ID: " << node->data->getCarId()
                      << " | Model: " << node->data->getModel()
                      << " | Price: $" << node->data->getPricePerDay()
                      << "/day\n";

            count++;

            if (count == 1)
                return node->data;
        }

        node = node->next;
    }

    if (count == 0)
    {
        std::cout << "No available cars found for brand: "
                  << brand << "\n";
    }
    else
    {
        std::cout << "\nFound " << count
                  << " available car(s) for brand: "
                  << brand << "\n";
    }

    return nullptr;
}

Car *Guest::searchCarById(const DoublyLinkedList<Car *> *carInventory,
                          int carId) const
{
    if (!carInventory)
    {
        std::cout << "Car inventory not available.\n";
        return nullptr;
    }

    auto node = carInventory->getHead();

    while (node)
    {
        if (node->data &&
            node->data->getCarId() == carId)
        {
            return node->data;
        }

        node = node->next;
    }

    std::cout << "Car #" << carId << " not found.\n";
    return nullptr;
}

void Guest::getCarDetails(const DoublyLinkedList<Car *> *carInventory,
                          int carId) const
{
    Car *car = searchCarById(carInventory, carId);

    if (!car)
        return;

    std::cout << "\nCar Details:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "ID: " << car->getCarId() << "\n";
    std::cout << "Plate: " << car->getLicensePlate() << "\n";
    std::cout << "Brand: " << car->getBrand() << "\n";
    std::cout << "Model: " << car->getModel() << "\n";
    std::cout << "Price: $" << car->getPricePerDay() << "/day\n";
    std::cout << "Status: " << car->getStatusString() << "\n";
}

bool Guest::isCarAvailable(const DoublyLinkedList<Car *> *carInventory,
                           int carId) const
{
    Car *car = searchCarById(carInventory, carId);

    if (!car)
        return false;

    bool available =
        (car->getStatus() == Car::Status::Available);

    std::cout << "Car #" << carId << " is "
              << (available ? "Available" : "Not Available")
              << ".\n";

    return available;
}

void Guest::commands()
{
    std::cout << "\nGuest Menu (Read-Only Access)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Available operations:\n";
    std::cout << "1. View all cars\n";
    std::cout << "2. Search by brand\n";
    std::cout << "3. View car details\n";
    std::cout << "4. Check availability\n";
    std::cout << "\nTo make reservations, please login as a Customer.\n";
}
