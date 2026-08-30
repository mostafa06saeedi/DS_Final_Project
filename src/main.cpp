
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"
#include "PriorityQueue.h"
#include "HashTable.h"
#include "Date.h"
#include "Car.h"
#include "User.h"
#include "Customer.h"
#include "Staff.h"
#include "Manager.h"
#include "MaintenanceUser.h"
#include "Guest.h"
#include "Config.h"

using namespace std;

class Exception : public std::exception
{
private:
    string message;

public:
    Exception(const string &msg) : message(msg) {}
    const char *what() const noexcept override { return message.c_str(); }
};

DoublyLinkedList<Car *> carInventory;
SinglyLinkedList<User *> allUsers;
SinglyLinkedList<Customer *> customers;
SinglyLinkedList<Staff *> staffMembers;
SinglyLinkedList<MaintenanceUser *> maintenanceUsers;
Manager *systemManager = nullptr;
HashMap<Customer *> customersByUsername;
HashMap<Staff *> staffByUsername;
HashMap<MaintenanceUser *> maintenanceByUsername;

void displayWelcome()
{
    cout << "\nCar Rental Management System\n";
    cout << "Data Structures Final Project\n\n";
}
void displayMainMenu()
{
    cout << "\nMain Menu\n";
    cout << "----------------------------------------\n";
    cout << "1. User Login\n";
    cout << "2. Register Customer\n";
    cout << "3. Register Staff (Admin Only)\n";
    cout << "4. Guest Access (View Cars)\n";
    cout << "5. View All Cars\n";
    cout << "6. System Information\n";
    cout << "0. Exit\n";
    cout << "Choose: ";
}

void initializeSampleData()
{
    cout << "\nInitializing sample data...\n";

    carInventory.insertBack(new Car(1, "TE-123", "Toyota", "Corolla", 150000));
    carInventory.insertBack(new Car(2, "TE-456", "Hyundai", "Elantra", 120000));
    carInventory.insertBack(new Car(3, "TE-789", "Nissan", "Santafe", 200000));
    carInventory.insertBack(new Car(4, "TE-010", "Peugeot", "405", 100000));
    carInventory.insertBack(new Car(5, "TE-101", "Honda", "Accord", 180000));

    cout << carInventory.size() << " cars loaded.\n";

    systemManager = new Manager("System", "admin", "admin123");
    allUsers.insertBack((User *)systemManager);
    systemManager->setRevenueCalculationRefs(&carInventory, &customers);

    cout << "System initialized successfully.\n";
}

void viewAllCars()
{
    if (carInventory.isEmpty())
    {
        cout << "No cars available.\n";
        return;
    }

    cout << "\nCar Inventory\n";
    cout << "----------------------------------------\n";

    auto node = carInventory.getHead();
    int count = 1;

    while (node)
    {
        cout << "\n"
             << count++ << ". Car #" << node->data->getCarId() << "\n";
        cout << "Brand: " << node->data->getBrand() << "\n";
        cout << "Model: " << node->data->getModel() << "\n";
        cout << "Plate: " << node->data->getLicensePlate() << "\n";
        cout << "Price per day: $" << node->data->getPricePerDay() << "\n";
        cout << "Status: " << node->data->getStatusString() << "\n";

        node = node->next;
    }

    cout << "\n";
}
void registerCustomer()
{
    cout << "\nCustomer Registration\n";
    cout << "----------------------------------------\n";

    string name, username, password;

    cout << "Full Name: ";
    getline(cin, name);
    if (name.empty() || name.length() > 100)
        throw Exception("Name must be non-empty and less than 100 characters.");

    cout << "Username: ";
    getline(cin, username);
    if (username.length() < 3 || username.length() > 50)
        throw Exception("Username must be between 3 and 50 characters.");

    if (customersByUsername.containsKey(username))
    {
        cout << "Username already exists.\n";
        return;
    }

    cout << "Password: ";
    getline(cin, password);
    if (password.length() < 6)
        throw Exception("Password must be at least 6 characters.");

    Customer *newCustomer = new Customer(name, username, password);

    customers.insertBack(newCustomer);
    allUsers.insertBack(static_cast<User *>(newCustomer));

    customersByUsername.put(username, newCustomer);

    cout << "Customer registered successfully.\n";
}
void registerStaff()
{
    cout << "\nStaff Registration (Admin Only)\n";
    cout << "----------------------------------------\n";

    string adminU, adminP;

    cout << "Admin Username: ";
    getline(cin, adminU);
    cout << "Admin Password: ";
    getline(cin, adminP);

    if (adminU != "admin" || adminP != "admin123")
    {
        cout << "Invalid admin credentials.\n";
        return;
    }

    string staffName, staffUsername, staffPassword;

    cout << "Staff Name: ";
    getline(cin, staffName);
    if (staffName.empty() || staffName.length() > 100)
        throw Exception("Name must be non-empty and less than 100 characters.");

    cout << "Staff Username: ";
    getline(cin, staffUsername);
    if (staffUsername.length() < 3 || staffUsername.length() > 50)
        throw Exception("Username must be between 3 and 50 characters.");

    if (staffByUsername.containsKey(staffUsername))
    {
        cout << "Username already exists.\n";
        return;
    }

    cout << "Staff Password: ";
    getline(cin, staffPassword);
    if (staffPassword.length() < 6)
        throw Exception("Password must be at least 6 characters.");

    Staff *newStaff = new Staff(staffName, staffUsername, staffPassword);

    staffMembers.insertBack(newStaff);
    allUsers.insertBack(static_cast<User *>(newStaff));

    staffByUsername.put(staffUsername, newStaff);

    cout << "Staff member registered successfully.\n";
}

void userLogin()
{
    cout << "\n--- User Login ---\n";
    string username, password;

    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    Customer **customer = customersByUsername.get(username);
    if (customer != nullptr)
    {
        Customer *cust = *customer;

        if (cust->getStatus() == User::Status::Deactive)
        {
            cout << "Account is deactivated. Contact administrator.\n";
            return;
        }

        if (cust->authenticate(password))
        {
            cout << "Login successful! Welcome, " << cust->getName() << "\n\n";

            cust->setCarCatalog(&carInventory);

            int userChoice = -1;
            while (userChoice != 0)
            {
                cout << "\n--- Customer Menu ---\n"
                     << "1. View Reservations\n"
                     << "2. View Active Rentals\n"
                     << "3. Create Reservation\n"
                     << "4. Pay Penalty\n"
                     << "0. Logout\n"
                     << "Choose: ";
                cin >> userChoice;
                cin.ignore();

                switch (userChoice)
                {
                case 1:
                    cust->viewReservations();
                    break;
                case 2:
                    cust->viewActiveRentals();
                    break;
                case 3:
                {
                    int carId;
                    cout << "Enter Car ID: ";
                    cin >> carId;
                    cin.ignore();
                    auto carNode = carInventory.getHead();
                    Car *targetCar = nullptr;
                    while (carNode)
                    {
                        if (carNode->data->getCarId() == carId)
                        {
                            targetCar = carNode->data;
                            break;
                        }
                        carNode = carNode->next;
                    }

                    if (!targetCar)
                    {
                        cout << "Car not found.\n";
                        break;
                    }

                    string startStr, endStr;
                    cout << "Start Date (YYYY/MM/DD): ";
                    getline(cin, startStr);
                    cout << "End Date (YYYY/MM/DD): ";
                    getline(cin, endStr);

                    // Parse dates
                    try
                    {
                        int startYear, startMonth, startDay;
                        int endYear, endMonth, endDay;
                        char slash;

                        istringstream startStream(startStr);
                        startStream >> startYear >> slash >> startMonth >> slash >> startDay;

                        istringstream endStream(endStr);
                        endStream >> endYear >> slash >> endMonth >> slash >> endDay;

                        Date startDate(startDay, startMonth, startYear);
                        Date endDate(endDay, endMonth, endYear);

                        if (startDate.isValid() && endDate.isValid())
                        {
                            cust->createReservation(targetCar, startDate, endDate);
                        }
                        else
                        {
                            cout << "Invalid date format.\n";
                        }
                    }
                    catch (const exception &e)
                    {
                        cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 4:
                {
                    double amount;
                    cout << "Enter penalty amount: $";
                    cin >> amount;
                    cin.ignore();
                    cust->payAmount(amount);
                    break;
                }
                case 0:
                    cout << "Logged out.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
                }
            }
            return;
        }
        else
        {
            cout << "Invalid password.\n";
            return;
        }
    }

    Staff **staff = staffByUsername.get(username);
    if (staff != nullptr)
    {
        Staff *s = *staff;

        if (s->getStatus() == User::Status::Deactive)
        {
            cout << "Account is deactivated. Contact administrator.\n";
            return;
        }

        if (s->authenticate(password))
        {
            cout << "Staff login successful! Welcome, " << s->getName() << "\n\n";

            s->setCarCatalog(&carInventory);

            int userChoice = -1;
            while (userChoice != 0)
            {
                cout << "\n--- Staff Menu ---\n"
                     << "1. Add New Car\n"
                     << "2. Convert Reservation to Rental\n"
                     << "3. Process Return (Calculate Penalty)\n"
                     << "4. Schedule Maintenance\n"
                     << "5. Complete Maintenance\n"
                     << "0. Logout\n"
                     << "Choose: ";
                cin >> userChoice;
                cin.ignore();

                switch (userChoice)
                {
                case 1:
                {
                    int carId;
                    string plate, brand, model;
                    double price;

                    cout << "Car ID: ";
                    cin >> carId;
                    cin.ignore();
                    cout << "License Plate: ";
                    getline(cin, plate);
                    cout << "Brand: ";
                    getline(cin, brand);
                    cout << "Model: ";
                    getline(cin, model);
                    cout << "Price per day ($): ";
                    cin >> price;
                    cin.ignore();

                    s->addNewCar(carId, plate, brand, model, price);
                    break;
                }
                case 2:
                {
                    int carId;
                    string customerUsername;
                    cout << "Enter Car ID: ";
                    cin >> carId;
                    cin.ignore();
                    cout << "Enter Customer Username: ";
                    getline(cin, customerUsername);

                    Customer **custPtr = customersByUsername.get(customerUsername);
                    if (custPtr && *custPtr)
                    {
                        s->convertReservationToRental(carId, *custPtr);
                    }
                    else
                    {
                        cout << "Customer not found.\n";
                    }
                    break;
                }
                case 3:
                {
                    int carId;
                    cout << "Enter Car ID: ";
                    cin >> carId;
                    cin.ignore();
                    Date today;
                    s->processReturn(carId, today);
                    break;
                }
                case 4:
                {
                    int carId;
                    string desc;
                    double cost;
                    cout << "Enter Car ID: ";
                    cin >> carId;
                    cin.ignore();
                    cout << "Maintenance Description: ";
                    getline(cin, desc);
                    cout << "Cost: $";
                    cin >> cost;
                    cin.ignore();
                    s->scheduleMaintenance(carId, desc, cost);
                    break;
                }
                case 5:
                {
                    int carId;
                    cout << "Enter Car ID to complete maintenance: ";
                    cin >> carId;
                    cin.ignore();
                    s->completeMaintenance(carId);
                    break;
                }
                case 0:
                    cout << "Logged out.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
                }
            }
            return;
        }
        else
        {
            cout << "Invalid password.\n";
            return;
        }
    }

    MaintenanceUser **maintenance = maintenanceByUsername.get(username);
    if (maintenance != nullptr)
    {
        MaintenanceUser *m = *maintenance;

        if (m->getStatus() == User::Status::Deactive)
        {
            cout << "Account is deactivated. Contact administrator.\n";
            return;
        }

        if (m->authenticate(password))
        {
            cout << "Maintenance User login successful! Welcome, " << m->getName() << "\n\n";

            int userChoice = -1;
            while (userChoice != 0)
            {
                cout << "\n--- Maintenance Menu ---\n"
                     << "1. View Maintenance Tasks\n"
                     << "2. Complete Maintenance\n"
                     << "0. Logout\n"
                     << "Choose: ";
                cin >> userChoice;
                cin.ignore();

                switch (userChoice)
                {
                case 1:
                    cout << "Viewing maintenance tasks...\n";
                    break;
                case 2:
                    cout << "Maintenance marked complete.\n";
                    break;
                case 0:
                    cout << "Logged out.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
                }
            }
            return;
        }
        else
        {
            cout << "Invalid password.\n";
            return;
        }
    }

    if (username == "admin" && password == "admin123")
    {
        cout << "Admin login successful!\n\n";

        int adminChoice = -1;
        while (adminChoice != 0)
        {
            cout << "\n--- Manager Menu ---\n"
                 << "1. View Revenue Report\n"
                 << "2. View Utilization Report\n"
                 << "3. Ban/Unban User\n"
                 << "4. Update System Settings\n"
                 << "5. Export Data (Backup)\n"
                 << "6. Import Data (Restore)\n"
                 << "0. Logout\n"
                 << "Choose: ";
            cin >> adminChoice;
            cin.ignore();

            switch (adminChoice)
            {
            case 1:
                systemManager->generateRevenueReport();
                break;
            case 2:
                systemManager->generateUtilizationReport();
                break;
            case 3:
            {
                string username;
                cout << "Enter customer username to ban: ";
                getline(cin, username);
                systemManager->banUser(username);
                break;
            }
            case 4:
                systemManager->updateConfig();
                break;
            case 5:
            {
                string filename;
                cout << "Enter backup filename: ";
                getline(cin, filename);
                if (systemManager->exportData(filename))
                    cout << "Backup created: " << filename << "\n";
                break;
            }
            case 6:
            {
                string filename;
                cout << "Enter restore filename: ";
                getline(cin, filename);
                if (systemManager->importData(filename))
                    cout << "Data restored from: " << filename << "\n";
                break;
            }
            case 0:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        }
        return;
    }

    cout << "Username not found or invalid credentials.\n";
}
void displaySystemInfo()
{
    cout << "\nSystem Information\n";
    cout << "------------------\n";
    cout << "Total Cars: " << carInventory.size() << "\n";
    cout << "Total Users: " << allUsers.size() << "\n";
    cout << "Customers: " << customers.size() << "\n";
    cout << "Staff: " << staffMembers.size() << "\n";
    cout << "Maintenance Users: " << maintenanceUsers.size() << "\n\n";

    cout << "Configuration:\n";
    cout << " - Max Rental Days: " << Config::MAX_RENTAL_DAYS << "\n";
    cout << " - Daily Penalty Rate: " << (Config::DAILY_PENALTY_RATE * 100) << "%\n";
    cout << " - Max Concurrent Reservations: " << Config::MAX_CONCURRENT_RESERVATIONS << "\n";
}
int main()
{
    try
    {
        displayWelcome();
        initializeSampleData();

        int mainChoice = -1;
        while (mainChoice != 0)
        {
            try
            {
                displayMainMenu();
                cout << "Choose an option: ";

                if (!(cin >> mainChoice))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }
                cin.ignore();

                switch (mainChoice)
                {
                case 1:
                    userLogin();
                    break;

                case 2:
                    registerCustomer();
                    break;

                case 3:
                    registerStaff();
                    break;

                case 4:
                {
                    cout << "\n--- Guest Access ---\n";
                    Guest guest("Guest", "guest", "guest123");

                    int guestChoice = -1;
                    while (guestChoice != 0)
                    {
                        cout << "\n--- Guest Menu ---\n"
                             << "1. View All Available Cars\n"
                             << "2. Search by Brand\n"
                             << "3. Check Car Details\n"
                             << "4. Check Car Availability\n"
                             << "0. Exit Guest Mode\n"
                             << "Choose: ";
                        if (!(cin >> guestChoice))
                        {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid input.\n";
                            continue;
                        }
                        cin.ignore();

                        switch (guestChoice)
                        {
                        case 1:
                            guest.viewAllCars(&carInventory);
                            break;

                        case 2:
                        {
                            string brand;
                            cout << "Enter brand to search: ";
                            getline(cin, brand);
                            guest.searchCarByBrand(&carInventory, brand);
                            break;
                        }

                        case 3:
                        {
                            int carId;
                            cout << "Enter Car ID: ";
                            if (!(cin >> carId))
                            {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "Invalid Car ID.\n";
                                continue;
                            }
                            cin.ignore();
                            guest.getCarDetails(&carInventory, carId);
                            break;
                        }

                        case 4:
                        {
                            int carId;
                            cout << "Enter Car ID: ";
                            if (!(cin >> carId))
                            {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "Invalid Car ID.\n";
                                continue;
                            }
                            cin.ignore();
                            guest.isCarAvailable(&carInventory, carId);
                            break;
                        }

                        case 0:
                            cout << "Exiting Guest mode.\n";
                            break;

                        default:
                            cout << "Invalid choice.\n";
                        }
                    }
                    break;
                }

                case 5:
                    viewAllCars();
                    break;

                case 6:
                    displaySystemInfo();
                    break;

                case 0:
                    cout << "\nGoodbye!\n";
                    break;

                default:
                    cout << "Invalid choice.\n";
                }
            }
            catch (const Exception &e)
            {
                cout << "Error: " << e.what() << "\n";
            }
            catch (const std::exception &e)
            {
                cout << "Unexpected error: " << e.what() << "\n";
            }
            catch (...)
            {
                cout << "Unknown error occurred.\n";
            }
        }

        return 0;
    }
    catch (const std::exception &e)
    {
        cout << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        cout << "Fatal unknown error.\n";
        return 1;
    }
}
