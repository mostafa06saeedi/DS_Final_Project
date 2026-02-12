#ifndef STAFF_H
#define STAFF_H
#include "User.h"
#include "Car.h"
#include "Contract.h"
#include "Date.h"
#include "DoublyLinkedList.h"

class Customer;

class Staff : public User
{
private:
    DoublyLinkedList<Car *> *carCatalog;

public:
    Staff(const std::string &name, const std::string &username,
          const std::string &password);

    void setCarCatalog(DoublyLinkedList<Car *> *catalog);

    bool addNewCar(int carId, const std::string &plate, const std::string &brand,
                   const std::string &model, double pricePerDay);
    bool convertReservationToRental(int carId, Customer *customer);
    bool processReturn(int carId, const Date &actualReturnDate);
    bool scheduleMaintenance(int carId, const std::string &desc, double cost);
    bool completeMaintenance(int carId);

    void commands() override;
};

#endif