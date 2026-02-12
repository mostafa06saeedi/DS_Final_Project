#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include "Config.h"
#include "SinglyLinkedList.h"
#include <string>

class Car;
class Customer;

template <typename T>
class DoublyLinkedList;

class Manager : public User
{
public:
    Manager(const std::string &name, const std::string &username,
            const std::string &password);

    void generateRevenueReport() const;
    void generateUtilizationReport() const;
    void banUser(const std::string &username);
    void updateConfig();

    bool exportData(const std::string &filename) const;
    bool importData(const std::string &filename);

    void commands() override;

    void setRevenueCalculationRefs(DoublyLinkedList<Car *> *cars,
                                   SinglyLinkedList<Customer *> *custs);

private:
    DoublyLinkedList<Car *> *carInventory = nullptr;
    SinglyLinkedList<Customer *> *customerList = nullptr;
};

#endif
