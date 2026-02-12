#ifndef CAR_H
#define CAR_H
#include <string>
#include "PriorityQueue.h"
#include "SinglyLinkedList.h"
#include "Contract.h"

class Car
{
public:
    enum class Status
    {
        Available,
        Reserved,
        Rented,
        Maintenance
    };

private:
    int carId;
    std::string licensePlate;
    std::string brand;
    std::string model;
    double pricePerDay;
    Status status;
    PriorityQueue<Contract *> activeRentals;
    SinglyLinkedList<Contract *> maintenanceHistory;
    PriorityQueue<Contract *> reservationQueue;

    int nextAvailableDay;

    void updateStatus();
    static bool compareByStartDate(Contract *const &a, Contract *const &b);
    static bool compareByReturnDate(Contract *const &a, Contract *const &b);

public:
    Car(int id, const std::string &plate, const std::string &brand,
        const std::string &model, double price);
    ~Car();

    int getCarId() const { return carId; }
    std::string getLicensePlate() const { return licensePlate; }
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    double getPricePerDay() const { return pricePerDay; }
    Status getStatus() const { return status; }
    std::string getStatusString() const;
    int getNextAvailableDay() const { return nextAvailableDay; }

    bool addReservation(Contract *reservation);
    Contract *startRental();
    void completeRental();
    void scheduleMaintenance(const std::string &desc, double cost);
    void completeMaintenance();

    Date getExpectedReturnDate() const;

    void printInfo() const;
    void printReservationQueue() const;
};
#endif
