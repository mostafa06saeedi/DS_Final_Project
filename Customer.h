#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

class Car;
class Contract;
class Date;

class Customer : public User
{
private:
    SinglyLinkedList<Contract *> activeContracts;
    SinglyLinkedList<Contract *> reservations;

    double totalPaid = 0.0;
    double penalty = 0.0;
    DoublyLinkedList<Car *> *carCatalog = nullptr;

public:
    Customer(const std::string &name,
             const std::string &userName,
             const std::string &password);

    virtual ~Customer();

    void setCarCatalog(DoublyLinkedList<Car *> *catalog) { carCatalog = catalog; }

    bool createReservation(Car *car, const Date &startDate, const Date &endDate);
    bool viewReservations() const;
    bool cancelReservation(const Date &startDate);
    void moveReservationToActive(Contract *contract);

    bool viewActiveRentals() const;
    bool extendRental(const Date &currentEndDate, const Date &newEndDate);

    double calculateTotalCost(int rentalDays) const;
    bool payAmount(double amount);

    double getPendingPenalty() const { return penalty; }
    void addPenalty(double amount) { penalty += amount; }

    double getTotalPaid() const { return totalPaid; }

    int getReservationCount() const { return reservations.size(); }
    int getActiveRentalCount() const { return activeContracts.size(); }

    void commands() override;

    friend class Staff;
    friend class Manager;
};

#endif
