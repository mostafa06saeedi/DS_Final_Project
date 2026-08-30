#include "Manager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Car.h"
#include "Customer.h"
#include "DoublyLinkedList.h"
#include "Config.h"

Manager::Manager(const std::string &name,
                 const std::string &username,
                 const std::string &password)
    : User(name, username, password, Status::Active),
      carInventory(nullptr),
      customerList(nullptr)
{
}

void Manager::setRevenueCalculationRefs(DoublyLinkedList<Car *> *cars,
                                        SinglyLinkedList<Customer *> *custs)
{
    carInventory = cars;
    customerList = custs;
}

void Manager::generateRevenueReport() const
{
    std::cout << "\n=== Revenue and Performance Report ===\n";
    std::cout << "----------------------------------------\n";

    if (!customerList || customerList->size() == 0)
    {
        std::cout << "No customers in the system.\n";
        return;
    }

    double totalRevenue = 0.0;
    int totalRentals = 0;
    int totalReservations = 0;

    auto node = customerList->getHead();
    while (node)
    {
        totalRevenue += node->data->getTotalPaid();
        totalRentals += node->data->getActiveRentalCount();
        totalReservations += node->data->getReservationCount();
        node = node->next;
    }

    std::cout << "Total Revenue: $"
              << std::fixed << std::setprecision(2)
              << totalRevenue << "\n";

    std::cout << "Total Rentals: " << totalRentals << "\n";
    std::cout << "Total Reservations: " << totalReservations << "\n";
    std::cout << "Total Customers: " << customerList->size() << "\n";

    if (totalRentals > 0)
    {
        double avgPerRental = totalRevenue / totalRentals;
        std::cout << "Average Revenue per Rental: $"
                  << avgPerRental << "\n";
    }

    std::ofstream csvFile("revenue_report.csv");
    if (csvFile.is_open())
    {
        csvFile << "Metric,Value\n";
        csvFile << "Total Revenue,$" << totalRevenue << "\n";
        csvFile << "Total Rentals," << totalRentals << "\n";
        csvFile << "Total Reservations," << totalReservations << "\n";
        csvFile << "Total Customers," << customerList->size() << "\n";
        csvFile.close();
        std::cout << "\nReport exported to: revenue_report.csv\n";
    }
}

void Manager::generateUtilizationReport() const
{
    std::cout << "\n=== Car Utilization Report ===\n";
    std::cout << "----------------------------------------\n";

    if (!carInventory || carInventory->size() == 0)
    {
        std::cout << "No cars in the system.\n";
        return;
    }

    int totalCars = carInventory->size();
    int availableCars = 0;
    int rentedCars = 0;
    int reservedCars = 0;
    int maintenanceCars = 0;

    auto node = carInventory->getHead();
    while (node)
    {
        switch (node->data->getStatus())
        {
        case Car::Status::Available:
            availableCars++;
            break;
        case Car::Status::Rented:
            rentedCars++;
            break;
        case Car::Status::Reserved:
            reservedCars++;
            break;
        case Car::Status::Maintenance:
            maintenanceCars++;
            break;
        }
        node = node->next;
    }

    double efficiencyRate =
        (totalCars > 0)
            ? ((rentedCars + reservedCars) * 100.0 / totalCars)
            : 0.0;

    std::cout << "Total Cars: " << totalCars << "\n";
    std::cout << "Available Cars: " << availableCars << "\n";
    std::cout << "Rented Cars: " << rentedCars << "\n";
    std::cout << "Reserved Cars: " << reservedCars << "\n";
    std::cout << "Maintenance Cars: " << maintenanceCars << "\n";

    std::cout << "Efficiency Rate: "
              << std::fixed << std::setprecision(1)
              << efficiencyRate << "%\n";

    std::ofstream csvFile("utilization_report.csv");
    if (csvFile.is_open())
    {
        csvFile << "Car Status,Count,Percentage\n";
        csvFile << "Total," << totalCars << ",100.0\n";
        csvFile << "Available," << availableCars << ","
                << (totalCars > 0 ? availableCars * 100.0 / totalCars : 0) << "\n";
        csvFile << "Rented," << rentedCars << ","
                << (totalCars > 0 ? rentedCars * 100.0 / totalCars : 0) << "\n";
        csvFile << "Reserved," << reservedCars << ","
                << (totalCars > 0 ? reservedCars * 100.0 / totalCars : 0) << "\n";
        csvFile << "Maintenance," << maintenanceCars << ","
                << (totalCars > 0 ? maintenanceCars * 100.0 / totalCars : 0) << "\n";
        csvFile.close();
        std::cout << "\nReport exported to: utilization_report.csv\n";
    }
}

void Manager::banUser(const std::string &username)
{
    if (!customerList)
    {
        std::cout << "Customer list not available.\n";
        return;
    }

    auto node = customerList->getHead();
    while (node)
    {
        if (node->data->getUserName() == username)
        {
            node->data->setStatus(User::Status::Deactive);
            std::cout << "User '" << username
                      << "' has been deactivated.\n";
            return;
        }
        node = node->next;
    }

    std::cout << "User '" << username
              << "' not found.\n";
}

void Manager::updateConfig()
{
    std::cout << "\nSystem Settings\n";
    std::cout << "----------------------------------------\n";

    std::cout << "1. Max Rental Days: "
              << Config::MAX_RENTAL_DAYS << "\n";

    std::cout << "2. Daily Penalty Rate: "
              << Config::DAILY_PENALTY_RATE << "\n";

    std::cout << "3. Max Concurrent Reservations: "
              << Config::MAX_CONCURRENT_RESERVATIONS << "\n";

    std::cout << "\nSelect option (1/2/3/0): ";

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int days;
        std::cout << "Enter max rental days: ";
        std::cin >> days;
        Config::setMaxRentalDays(days);
        std::cout << "Setting updated.\n";
        break;
    }
    case 2:
    {
        double rate;
        std::cout << "Enter daily penalty rate (0.0 - 1.0): ";
        std::cin >> rate;
        Config::setPenaltyRate(rate);
        std::cout << "Setting updated.\n";
        break;
    }
    case 3:
    {
        int maxRes;
        std::cout << "Enter max concurrent reservations: ";
        std::cin >> maxRes;
        Config::setMaxReservations(maxRes);
        std::cout << "Setting updated.\n";
        break;
    }
    default:
        std::cout << "Invalid choice.\n";
    }
}

bool Manager::exportData(const std::string &filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Cannot open file '" << filename
                  << "' for writing.\n";
        return false;
    }

    file << "[CONFIG]\n";
    file << "MAX_RENTAL_DAYS=" << Config::MAX_RENTAL_DAYS << "\n";
    file << "DAILY_PENALTY_RATE=" << Config::DAILY_PENALTY_RATE << "\n";
    file << "MAX_CONCURRENT_RESERVATIONS="
         << Config::MAX_CONCURRENT_RESERVATIONS << "\n";
    file << "[END]\n\n";

    file << "[CARS]\n";
    if (carInventory && carInventory->size() > 0)
    {
        auto carNode = carInventory->getHead();
        while (carNode)
        {
            file << carNode->data->getCarId() << ","
                 << carNode->data->getLicensePlate() << ","
                 << carNode->data->getBrand() << ","
                 << carNode->data->getModel() << ","
                 << carNode->data->getPricePerDay() << ","
                 << carNode->data->getStatusString() << "\n";
            carNode = carNode->next;
        }
    }
    file << "[END]\n\n";

    file << "[CUSTOMERS]\n";
    if (customerList && customerList->size() > 0)
    {
        auto custNode = customerList->getHead();
        while (custNode)
        {
            file << custNode->data->getUserName() << ","
                 << custNode->data->getName() << ","
                 << (custNode->data->getStatus() == User::Status::Active ? "Active" : "Deactive") << "\n";
            custNode = custNode->next;
        }
    }
    file << "[END]\n";

    file.close();

    std::cout << "Full system data exported successfully to '"
              << filename << "'\n";
    return true;
}

bool Manager::importData(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Cannot open file '" << filename
                  << "' for reading.\n";
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.find("MAX_RENTAL_DAYS=") != std::string::npos)
        {
            int days =
                std::stoi(line.substr(line.find("=") + 1));
            Config::setMaxRentalDays(days);
        }
        else if (line.find("DAILY_PENALTY_RATE=") != std::string::npos)
        {
            double rate =
                std::stod(line.substr(line.find("=") + 1));
            Config::setPenaltyRate(rate);
        }
        else if (line.find("MAX_CONCURRENT_RESERVATIONS=") != std::string::npos)
        {
            int count =
                std::stoi(line.substr(line.find("=") + 1));
            Config::setMaxReservations(count);
        }
    }

    file.close();

    std::cout << "Data imported successfully from "
              << filename << "\n";

    return true;
}

void Manager::commands()
{
    std::cout << "\nManager Menu\n";
    std::cout << "----------------------------------------\n";
    std::cout << "1. Revenue Report\n";
    std::cout << "2. Car Utilization Report\n";
    std::cout << "3. Ban User\n";
    std::cout << "4. System Settings\n";
    std::cout << "5. Export Data\n";
    std::cout << "6. Import Data\n";
    std::cout << "0. Exit\n";
}
