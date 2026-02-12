#include "Car.h"
#include <iostream>
#include <iomanip>

bool Car::compareByStartDate(Contract *const &a, Contract *const &b)
{
    return a->getStartDate() < b->getStartDate();
}

bool Car::compareByReturnDate(Contract *const &a, Contract *const &b)
{
    return a->getReturnDate() < b->getReturnDate();
}

Car::Car(int id, const std::string &plate, const std::string &brand,
         const std::string &model, double price)
    : carId(id), licensePlate(plate), brand(brand), model(model),
      pricePerDay(price), status(Status::Available), nextAvailableDay(0)
{
    reservationQueue.create(compareByStartDate);
    activeRentals.create(compareByReturnDate);
}

Car::~Car() {}

void Car::updateStatus()
{
    if (status == Status::Maintenance)
        return;

    if (!activeRentals.isEmpty())
    {
        status = Status::Rented;
        nextAvailableDay = activeRentals.peek()->getReturnDate().toAbsoluteDays();
    }
    else if (!reservationQueue.isEmpty())
    {
        status = Status::Reserved;
        nextAvailableDay = reservationQueue.peek()->getStartDate().toAbsoluteDays();
    }
    else
    {
        status = Status::Available;
        nextAvailableDay = 0;
    }
}

std::string Car::getStatusString() const
{
    switch (status)
    {
    case Status::Available:
        return "Available";
    case Status::Reserved:
        return "Reserved";
    case Status::Rented:
        return "Rented";
    case Status::Maintenance:
        return "Maintenance";
    default:
        return "Unknown";
    }
}

bool Car::addReservation(Contract *reservation)
{
    if (status == Status::Maintenance)
    {
        std::cout << "Car #" << carId << " is under maintenance.\n";
        return false;
    }

    if (!activeRentals.isEmpty())
    {
        Contract *current = activeRentals.peek();
        if (reservation->getStartDate() < current->getReturnDate())
        {
            std::cout << "Time conflict with active rental (returns on "
                      << current->getReturnDate().toString() << ").\n";
            return false;
        }
    }

    for (int i = 0; i < reservationQueue.getCount(); ++i)
    {
        Contract *existing = reservationQueue.getAt(i);
        if (existing)
        {
            if ((reservation->getStartDate() < existing->getReturnDate()) &&
                (reservation->getReturnDate() > existing->getStartDate()))
            {
                std::cout << "Time conflict with existing reservation ("
                          << existing->getStartDate().toString() << " to "
                          << existing->getReturnDate().toString() << ").\n";
                return false;
            }
        }
    }

    reservationQueue.push(reservation);
    updateStatus();

    std::cout << "Reservation added for Car #" << carId
              << " (starts "
              << reservation->getStartDate().toString() << ")\n";

    return true;
}

Contract *Car::startRental()
{
    if (reservationQueue.isEmpty())
    {
        std::cout << "No pending reservations for Car #" << carId << ".\n";
        return nullptr;
    }

    Contract *reservation = reservationQueue.peek();
    reservationQueue.pop();

    reservation->changeType(Contract::Type::Rent);
    activeRentals.push(reservation);

    updateStatus();

    std::cout << "Rental started for Car #" << carId
              << " (Customer: " << reservation->getCustomerId() << ")\n";

    return reservation;
}

void Car::completeRental()
{
    if (activeRentals.isEmpty())
    {
        std::cout << "No active rental to complete for Car #" << carId << ".\n";
        return;
    }

    Contract *current = activeRentals.peek();

    std::cout << "Rental completed for Car #" << carId
              << " (Customer: " << current->getCustomerId() << ")\n";

    activeRentals.pop();
    updateStatus();

    if (!reservationQueue.isEmpty() && status != Status::Maintenance)
    {
        std::cout << "Next reservation starts on "
                  << reservationQueue.peek()->getStartDate().toString() << ".\n";
    }
}

void Car::scheduleMaintenance(const std::string &desc, double cost)
{
    Date today;
    Date endDate(today.getDay(), today.getMonth(), today.getYear());

    Contract *maintenanceContract = new Contract(
        this,
        nullptr,
        today,
        endDate,
        Contract::Type::Maintain);

    maintenanceHistory.insertBack(maintenanceContract);

    status = Status::Maintenance;
    nextAvailableDay = -1;

    std::cout << "Maintenance scheduled for Car #"
              << carId << "\n";
    std::cout << "Date: " << today.toString() << "\n";
    std::cout << "Cost: $" << std::fixed << std::setprecision(2) << cost << "\n";
}

void Car::completeMaintenance()
{
    if (status != Status::Maintenance)
    {
        std::cout << "Car #" << carId << " is not under maintenance.\n";
        return;
    }

    status = Status::Available;
    nextAvailableDay = 0;

    std::cout << "Maintenance completed for Car #" << carId << ".\n";
    std::cout << "Car is now available for rental/reservation.\n";
    updateStatus();
}

Date Car::getExpectedReturnDate() const
{
    if (activeRentals.isEmpty())
    {
        return Date();
    }

    Contract *current = activeRentals.peek();
    return current->getReturnDate();
}

void Car::printInfo() const
{
    std::cout << "\nCar #" << carId << "\n"
              << "Plate: " << licensePlate << "\n"
              << "Model: " << brand << " " << model << "\n"
              << "Price per day: $" << pricePerDay << "\n"
              << "Status: " << getStatusString() << "\n"
              << "Next available: ";

    if (nextAvailableDay == 0)
        std::cout << "Now\n";
    else if (nextAvailableDay == -1)
        std::cout << "After maintenance\n";
    else
        std::cout << "Day " << nextAvailableDay << "\n";

    std::cout << "Active rentals: " << activeRentals.size() << "\n"
              << "Pending reservations: " << reservationQueue.size() << "\n";
}

void Car::printReservationQueue() const
{
    if (reservationQueue.isEmpty())
    {
        std::cout << "No pending reservations for Car #" << carId << ".\n";
        return;
    }

    std::cout << "Reservation queue for Car #" << carId << ":\n";
    std::cout << "Total pending reservations: "
              << reservationQueue.size() << "\n\n";

    for (int i = 0; i < reservationQueue.getCount(); ++i)
    {
        const Contract *contract = reservationQueue.getAt(i);
        if (contract)
        {
            std::cout << i + 1 << ". Start: "
                      << contract->getStartDate().toString()
                      << " | End: "
                      << contract->getEndDate().toString()
                      << " | Customer: "
                      << contract->getCustomerId() << "\n";
        }
    }
}
