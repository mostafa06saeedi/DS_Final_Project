#include "Customer.h"
#include "Car.h"
#include "Contract.h"
#include "Date.h"
#include "Config.h"
#include <iostream>
#include <iomanip>

Customer::Customer(const std::string &name,
                   const std::string &userName,
                   const std::string &password)
    : User(name, userName, password, Status::Active),
      totalPaid(0.0), penalty(0.0)
{
}

Customer::~Customer()
{
    auto node = activeContracts.getHead();
    while (node)
    {
        delete node->data;
        node = node->next;
    }
    activeContracts.clear();

    node = reservations.getHead();
    while (node)
    {
        delete node->data;
        node = node->next;
    }
    reservations.clear();
}

bool Customer::createReservation(Car *car, const Date &startDate, const Date &endDate)
{
    if (getStatus() != Status::Active)
    {
        std::cout << "Account is inactive.\n";
        return false;
    }

    if (car == nullptr)
    {
        std::cout << "Invalid car.\n";
        return false;
    }

    if (endDate < startDate)
    {
        std::cout << "End date cannot be before start date.\n";
        return false;
    }

    if (reservations.size() >= static_cast<int>(Config::MAX_CONCURRENT_RESERVATIONS))
    {
        std::cout << "Maximum number of reservations reached.\n";
        return false;
    }

    try
    {
        Contract *newReservation =
            new Contract(car, (User *)this, startDate, endDate, Contract::Type::Reserve);

        reservations.insertBack(newReservation);

        car->addReservation(newReservation);

        std::cout << "Reservation created successfully.\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error creating reservation: " << e.what() << "\n";
        return false;
    }
}

bool Customer::viewReservations() const
{
    if (reservations.isEmpty())
    {
        std::cout << "No reservations found.\n";
        return false;
    }

    std::cout << "\nYour Reservations:\n";
    std::cout << "-----------------------------------\n";

    auto node = reservations.getHead();
    int count = 1;

    while (node)
    {
        const Contract *contract = node->data;

        std::cout << count++ << ". Car: "
                  << contract->getCar()->getBrand()
                  << " | From: " << contract->getStartDate().toString()
                  << " | To: " << contract->getEndDate().toString()
                  << "\n";

        node = node->next;
    }

    return true;
}

bool Customer::cancelReservation(const Date &startDate)
{
    auto node = reservations.getHead();

    while (node)
    {
        if (node->data->getStartDate() == startDate)
        {
            Contract *contract = node->data;
            reservations.remove(node);
            delete contract;

            std::cout << "Reservation cancelled successfully.\n";
            return true;
        }

        node = node->next;
    }

    std::cout << "Reservation not found.\n";
    return false;
}

void Customer::moveReservationToActive(Contract *contract)
{
    if (!contract)
        return;

    auto node = reservations.getHead();
    while (node)
    {
        if (node->data == contract)
        {
            reservations.remove(node);
            break;
        }
        node = node->next;
    }
    activeContracts.insertBack(contract);
}

bool Customer::viewActiveRentals() const
{
    if (activeContracts.isEmpty())
    {
        std::cout << "No active rentals.\n";
        return false;
    }

    std::cout << "\nActive Rentals:\n";
    std::cout << "-----------------------------------\n";

    auto node = activeContracts.getHead();
    int count = 1;

    while (node)
    {
        const Contract *contract = node->data;
        long days = contract->getDuration();

        std::cout << count++ << ". Car: "
                  << contract->getCar()->getBrand()
                  << " | Duration: " << days << " days"
                  << " | Daily price: "
                  << contract->getCar()->getPricePerDay()
                  << "\n";

        node = node->next;
    }

    return true;
}

bool Customer::extendRental(const Date &currentEndDate, const Date &newEndDate)
{
    if (newEndDate <= currentEndDate)
    {
        std::cout << "New date must be later than current end date.\n";
        return false;
    }

    auto node = activeContracts.getHead();

    while (node)
    {
        if (node->data->getEndDate() == currentEndDate)
        {
            node->data->timeExtend(newEndDate.daysBetween(currentEndDate));

            std::cout << "Rental extended until "
                      << newEndDate.toString() << ".\n";

            return true;
        }

        node = node->next;
    }

    std::cout << "Rental not found.\n";
    return false;
}

double Customer::calculateTotalCost(int rentalDays) const
{
    if (activeContracts.isEmpty())
        return 0.0;

    auto node = activeContracts.getHead();
    const Contract *contract = node->data;

    double dailyRate = contract->getCar()->getPricePerDay();
    return dailyRate * rentalDays;
}

bool Customer::payAmount(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid payment amount.\n";
        return false;
    }

    if (penalty > 0)
    {
        if (amount >= penalty)
        {
            amount -= penalty;
            penalty = 0;
            std::cout << "Penalty paid in full.\n";
        }
        else
        {
            penalty -= amount;
            std::cout << "Partial penalty payment. Remaining penalty: "
                      << penalty << "\n";
            return true;
        }
    }

    totalPaid += amount;

    std::cout << "Payment of "
              << std::fixed << std::setprecision(2)
              << amount << " completed successfully.\n";

    return true;
}

void Customer::commands()
{
    std::cout << "\nCustomer Menu\n";
    std::cout << "-----------------------------------\n";
    std::cout << "1. View car list\n";
    std::cout << "2. Search car\n";
    std::cout << "3. Make reservation\n";
    std::cout << "4. View reservations\n";
    std::cout << "5. Cancel reservation\n";
    std::cout << "6. View active rentals\n";
    std::cout << "7. Extend rental\n";
    std::cout << "8. Pay penalty\n";
    std::cout << "0. Exit\n";
}
