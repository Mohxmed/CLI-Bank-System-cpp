# C++ CLI Bank System - OOP Learning Project
## Overview
This project is a **C++ Command Line Interface (CLI)** Bank System, developed as a learning exercise to practice and implement **Object-Oriented Programming (OOP)** concepts. It simulates basic banking operations like managing clients, handling transactions, updating client information, and managing users, all while using fundamental OOP principles.
## Purpose
The primary goal of this project is to:
- Apply **OOP concepts** such as classes, objects, inheritance, polymorphism, and encapsulation.
- Develop practical skills in C++ programming, especially for handling **real-world scenarios** like managing accounts and clients in a bank system.
- Gain hands-on experience with **data structures** and algorithms as part of a practical C++ project.
## Key OOP Concepts Implemented
### 1. **Classes and Objects**:
   - **Client Class**: Represents a client with personal information (e.g., name, account number, balance).
   - **Bank Class**: Encapsulates operations such as adding new clients, deleting clients, and performing transactions.
   - **Transaction Class**: Handles the deposit and withdrawal operations and keeps track of transactions.
   
### 2. **Encapsulation**:
   - Client data, such as account balance and personal information, is kept private within the `Client` class. Public getter and setter functions are used to access and modify this data.
   
### 3. **Inheritance**:
   - The project utilizes inheritance to model different user roles (e.g., **Admin** and **Customer**) using a base class `User` and derived classes for specific roles.
   
### 4. **Polymorphism**:
   - Functions like `viewClientDetails()` or `performTransaction()` are overridden in derived classes to handle different types of users (Admin vs Customer).
### 5. **Abstraction**:
   - Certain operations, such as transaction processing and client management, are abstracted through classes and functions to make the system easier to maintain and expand.
## Features
- **Client Management**:
   - Add, delete, and update client details.
   - View client information like account balance and transaction history.
- **Account Operations**:
   - Deposit and withdrawal operations.
   - Perform transactions with proper validation and error checking.
- **User Management**:
   - Manage user roles (Admin and Customer) with different access levels.
- **Data Persistence**:
   - Data is temporarily stored in the program’s runtime (this can be expanded with file handling or database connections).
## Requirements
- **Compiler**: C++14 or later.
- **IDE**: Any C++ IDE or text editor (e.g., Visual Studio Code, Code::Blocks, or CLion).
## Setup & Running
1. Clone or download this repository.
2. Open the project in your C++ IDE or text editor.
3. Compile and run the `main.cpp` file to start the CLI Bank System.
4. Interact with the system through the command-line interface.

Login Details in FileStorage/Users.txt Are Encrypted<br>
Username: "Mhmd", Password: "1234"
