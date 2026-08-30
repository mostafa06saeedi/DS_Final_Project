# 🚗 Car Rental Management System

A full-featured **Car Rental Management System** built in C++ — the final project for a Data Structures course. Every core data structure (linked lists, queues, priority queues, hash tables) is implemented **from scratch** and used to power a realistic, role-based rental platform.

---

## ✨ Features

### 👥 Role-Based Access
- **Guest** — browse the available car catalog with no account needed
- **Customer** — register, rent cars, manage active/past contracts
- **Staff** — handle rentals, returns, and maintenance scheduling
- **Manager** — full admin access: revenue & utilization reports, user bans, system configuration, data import/export

### 🚘 Car & Fleet Management
- Track each car's live status: `Available`, `Reserved`, `Rented`, `Maintenance`
- Automatic reservation queueing — cars can hold a waitlist of pending reservations
- Maintenance history tracking per vehicle

### 📄 Contracts
- Unified `Contract` model covering **Rent**, **Reserve**, **Maintain**, and **Extend** operations
- Rental extension and type-changing support
- Duration and return-date calculations built on a custom date engine

### 📅 Custom Shamsi (Persian) Calendar
- `Date` is a from-scratch implementation of the **Persian (Shamsi) calendar** — not `<chrono>`, not `<ctime>`
- Handles leap years, days-per-month, and date arithmetic (`daysBetween`, comparisons, absolute day conversion) entirely manually

### 🔐 Authentication
- Password hashing for all user accounts
- Active/inactive account status management

### 📊 Reporting
- Revenue reports and fleet utilization analytics for managers
- JSON-free data import/export for backups

---

## 🧠 Data Structures — Built From Scratch

This is the heart of the project: every structure below is a hand-rolled, templated implementation (no STL containers used for the core logic).

| Structure | Used For |
|---|---|
| **Singly Linked List** | Storing users, customers, staff, maintenance history |
| **Doubly Linked List** | Car inventory management |
| **Priority Queue** | Ordering active rentals and the reservation waitlist by date |
| **Queue** | FIFO processing where order of arrival matters |
| **Hash Table** | O(1) customer lookup by username |

---

## 📂 Project Structure

```
.
├── include/          # Header files (.h) and template implementations (.tpp)
├── src/              # Source files (.cpp), including main.cpp
├── CMakeLists.txt    # Build configuration
└── .gitignore
```

> **Note:** Template classes (`DoublyLinkedList`, `SinglyLinkedList`, `Queue`, `PriorityQueue`, `HashTable`) ship their `.h` declaration and `.tpp` implementation together in `include/`, since C++ template definitions must be visible at the point of instantiation.

---

## 🚀 Getting Started

### Option 1 — Build with CMake (recommended)
```bash
mkdir build && cd build
cmake ..
cmake --build .
./CarRentalSystem
```

### Option 2 — Compile directly with g++
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o CarRentalSystem
./CarRentalSystem
```

### Using the App
On launch, the system seeds itself with sample cars and drops you into the main menu:
```
1. User Login
2. Register Customer
3. Register Staff (Admin Only)
4. Guest Access (View Cars)
5. View All Cars
6. System Information
0. Exit
```

---

## 🗂️ File Overview

| File | Responsibility |
|---|---|
| `Car.*` | Vehicle entity, status tracking, reservation queue |
| `Contract.*` | Rent/reserve/maintain/extend agreements between users and cars |
| `Maintain.*` | Maintenance-specific contract subtype |
| `Date.*` | Custom Shamsi (Persian) calendar implementation |
| `User.*` | Abstract base class for all account roles |
| `Customer.*` / `Staff.*` / `Manager.*` / `MaintenanceUser.*` / `Guest.*` | Role-specific behavior, inheriting from `User` |
| `Config.*` | System-wide tunables (max rental days, penalty rate, reservation limits) |
| `SinglyLinkedList.* ` / `DoublyLinkedList.*` | Custom linked list templates |
| `Queue.*` / `PriorityQueue.*` | Custom queue templates |
| `HashTable.*` | Custom hash table template (username → customer lookup) |

---

## 👨‍💻 Contributors
- **Mostafa** — Lead developer and sole contributor. Responsible for all stages of design, development, testing, and execution of this project.
