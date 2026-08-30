#ifndef GUEST_H
#define GUEST_H

#include "User.h"

class Car;
template <typename T>
class DoublyLinkedList;

class Guest : public User
{
public:
    Guest(const std::string &name,
          const std::string &userName,
          const std::string &password);

    virtual ~Guest();

    void viewAllCars(const DoublyLinkedList<Car *> *carInventory) const;
    Car *searchCarByBrand(const DoublyLinkedList<Car *> *carInventory,
                          const std::string &brand) const;
    Car *searchCarById(const DoublyLinkedList<Car *> *carInventory,
                       int carId) const;
    void getCarDetails(const DoublyLinkedList<Car *> *carInventory,
                       int carId) const;
    bool isCarAvailable(const DoublyLinkedList<Car *> *carInventory,
                        int carId) const;

    void commands() override;
};

#endif