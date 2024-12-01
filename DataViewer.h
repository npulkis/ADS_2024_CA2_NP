#pragma once
#include <string>
#include "Employee.h"
#include "TreeMap.h"
#include "binarytree.h"

class DataViewer {
public:
    void run();
private:
    bool readCSV(const std::string& filename, Employee*& employees, int& count);
    void createIndex(Employee* employees, int count, const std::string& fieldName, TreeMap<std::string, BinaryTree<int>>& index);
    void viewSubset(Employee* employees, int count, const std::string& fieldName, const std::string& value);
    void displayEmployee(const Employee& emp);
};
