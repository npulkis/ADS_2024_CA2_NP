#include "DataViewer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include <stack>

void DataViewer::run() {
    Employee* employees = nullptr;
    int employeeCount = 0;

     "employee_records.csv";
    std::cout << "Enter the CSV filename to read: ";
    std::string inputFilename;
    std::getline(std::cin, inputFilename);
   
   std::string filename = inputFilename;


    if (!readCSV(filename, employees, employeeCount)) {
        std::cerr << "Failed to read the CSV file." << std::endl;
        return;
    }

    int dataChoice = 0;
    while (dataChoice != 3) {
        std::cout << "\nData Viewer Menu:\n";
        std::cout << "1. Create an index based on a field\n";
        std::cout << "2. View a subset of data based on a field value\n";
        std::cout << "3. Return to Main Menu\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> dataChoice;
        std::cin.ignore();

        if (dataChoice == 1) {
            std::cout << "Enter the field name to index on (EmployeeID, Name, Department, Age, Salary, EmploymentDate): ";
            std::string fieldName;
            std::getline(std::cin, fieldName);

            TreeMap<std::string, BinaryTree<int>> index;
            createIndex(employees, employeeCount, fieldName, index);

            BinaryTree<std::string> keys = index.keySet();
            std::cout << "\nUnique values and counts for field '" << fieldName << "':\n";
            std::cout << std::left << std::setw(30) << "Value" << "Count\n";
            std::cout << "-------------------------------------------\n";

            std::stack<BSTNode<std::string>*> nodeStack;
            BSTNode<std::string>* current = keys.root;

            while (!nodeStack.empty() || current != nullptr) {
                while (current != nullptr) {
                    nodeStack.push(current);
                    current = current->getLeft();
                }

                current = nodeStack.top();
                nodeStack.pop();

                std::string key = current->getItem();
                BinaryTree<int>* idSet = index.get(key);
                int count = idSet->count();
                std::cout << std::left << std::setw(30) << key << count << "\n";

                current = current->getRight();
            }

        }
        else if (dataChoice == 2) {
            std::cout << "Enter the field name to search on (EmployeeID, Name, Department, Age, Salary, EmploymentDate): ";
            std::string fieldName;
            std::getline(std::cin, fieldName);
            std::cout << "Enter the value to search for: ";
            std::string value;
            std::getline(std::cin, value);

            viewSubset(employees, employeeCount, fieldName, value);
        }
        else if (dataChoice == 3) {
            std::cout << "Returning to Main Menu." << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please select 1, 2, or 3." << std::endl;
        }
    }
    delete[] employees;
}

bool DataViewer::readCSV(const std::string& filename, Employee*& employees, int& count) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    int numRecords = -1;
    while (std::getline(file, line)) {
        numRecords++;
    }

    if (numRecords <= 0) {
        return false;
    }

    employees = new Employee[numRecords];
    count = numRecords;

    file.clear();
    file.seekg(0);

    std::getline(file, line);

    int index = 0;
    while (std::getline(file, line) && index < numRecords) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int employeeID = std::stoi(token);

        std::getline(ss, token, ',');
        std::string name = token;

        std::getline(ss, token, ',');
        std::string department = token;

        std::getline(ss, token, ',');
        int age = std::stoi(token);

        std::getline(ss, token, ',');
        double salary = std::stod(token);

        std::getline(ss, token, ',');
        std::string employmentDate = token;

        employees[index] = Employee(employeeID, name, department, age, salary, employmentDate);
        index++;
    }

    file.close();
    return true;
}

void DataViewer::createIndex(Employee* employees, int count, const std::string& fieldName, TreeMap<std::string, BinaryTree<int>>& index) {
    for (int i = 0; i < count; i++) {
        std::string key;
        if (fieldName == "EmployeeID") {
            key = std::to_string(employees[i].EmployeeID);
        }
        else if (fieldName == "Name") {
            key = employees[i].Name;
        }
        else if (fieldName == "Department") {
            key = employees[i].Department;
        }
        else if (fieldName == "Age") {
            key = std::to_string(employees[i].Age);
        }
        else if (fieldName == "Salary") {
            key = std::to_string(employees[i].Salary);
        }
        else if (fieldName == "EmploymentDate") {
            key = employees[i].EmploymentDate;
        }
        else {
            std::cout << "Invalid field name." << std::endl;
            return;
        }

        BinaryTree<int>* idSet = index.get(key);
        if (idSet == nullptr) {
            BinaryTree<int> newSet;
            newSet.add(employees[i].EmployeeID);
            index.put(key, newSet);
        }
        else {
            idSet->add(employees[i].EmployeeID);
        }
    }
}

void DataViewer::viewSubset(Employee* employees, int count, const std::string& fieldName, const std::string& value) {
    Employee* subset = new Employee[count];
    int subsetCount = 0;

    for (int i = 0; i < count; i++) {
        bool match = false;
        if (fieldName == "EmployeeID") {
            match = std::to_string(employees[i].EmployeeID) == value;
        }
        else if (fieldName == "Name") {
            match = employees[i].Name == value;
        }
        else if (fieldName == "Department") {
            match = employees[i].Department == value;
        }
        else if (fieldName == "Age") {
            match = std::to_string(employees[i].Age) == value;
        }
        else if (fieldName == "Salary") {
            match = std::to_string(employees[i].Salary) == value;
        }
        else if (fieldName == "EmploymentDate") {
            match = employees[i].EmploymentDate == value;
        }
        else {
            std::cout << "Invalid field name." << std::endl;
            delete[] subset;
            return;
        }

        if (match) {
            subset[subsetCount++] = employees[i];
        }
    }

    if (subsetCount == 0) {
        std::cout << "No records found matching the criteria." << std::endl;
    }
    else {
        std::cout << "\nMatching Records:\n";
        std::cout << std::left
            << std::setw(10) << "EmpID"
            << std::setw(25) << "Name"
            << std::setw(15) << "Department"
            << std::setw(5) << "Age"
            << std::setw(12) << "Salary"
            << std::setw(15) << "EmploymentDate"
            << "\n";
        std::cout << "-------------------------------------------------------------------------------\n";
        for (int i = 0; i < subsetCount; i++) {
            displayEmployee(subset[i]);
        }
    }

    delete[] subset;
}

void DataViewer::displayEmployee(const Employee& emp) {
    std::cout << std::left
        << std::setw(10) << emp.EmployeeID
        << std::setw(25) << emp.Name
        << std::setw(15) << emp.Department
        << std::setw(5) << emp.Age
        << std::setw(12) << emp.Salary
        << std::setw(15) << emp.EmploymentDate
        << "\n";
}
