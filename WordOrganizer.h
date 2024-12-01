#pragma once
#include <string>
#include "TreeMap.h"
#include "binarytree.h"

class WordOrganizer {
public:
    void run();
private:
    TreeMap<char, BinaryTree<std::string>> wordMap;

    void processLine(const std::string& inputLine);
    bool treeContains(BSTNode<std::string>* node, const std::string& item);
    void displayMenu();
};
