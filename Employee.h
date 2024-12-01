#pragma once
#include <string>

struct Employee {
    int EmployeeID;
    std::string Name;
    std::string Department;
    int Age;
    double Salary;
    std::string EmploymentDate;

    Employee() {}

    Employee(int id, const std::string& name, const std::string& dept, int age, double salary, const std::string& date)
        : EmployeeID(id), Name(name), Department(dept), Age(age), Salary(salary), EmploymentDate(date) {}
};
