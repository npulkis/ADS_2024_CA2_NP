#include "WordOrganizer.h"
#include <iostream>
#include <fstream>
#include <cctype>

void WordOrganizer::run() {
    std::string filename;
    std::cout << "Enter the filename to read: ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file '" << filename << "'." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        processLine(line);
    }

    file.close();

    displayMenu();
}

void WordOrganizer::processLine(const std::string& inputLine) {
    std::string line = inputLine;
    size_t i = 0;
    while (i < line.length()) {
        while (i < line.length() && !std::isalpha(static_cast<unsigned char>(line[i]))) {
            i++;
        }

        size_t start = i;

        while (i < line.length() && std::isalpha(static_cast<unsigned char>(line[i]))) {
            line[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(line[i])));
            i++;
        }

        size_t end = i;

        if (start < end) {
            std::string word = line.substr(start, end - start);
            char firstLetter = word[0];

            BinaryTree<std::string>* wordSet = wordMap.get(firstLetter);

            if (wordSet == nullptr) {
                BinaryTree<std::string> newSet;
                newSet.add(word);
                wordMap.put(firstLetter, newSet);
            }
            else {
                if (!treeContains(wordSet->root, word)) {
                    wordSet->add(word);
                }
            }
        }
    }
}

bool WordOrganizer::treeContains(BSTNode<std::string>* node, const std::string& item) {
    if (node == nullptr)
        return false;
    if (node->getItem() == item)
        return true;
    else if (item < node->getItem())
        return treeContains(node->getLeft(), item);
    else
        return treeContains(node->getRight(), item);
}

void WordOrganizer::displayMenu() {
    int choice = 0;

    while (choice != 3) {
        std::cout << "1. View list of letters\n";
        std::cout << "2. View words associated with a letter\n";
        std::cout << "3. Return to Main Menu\n";
        std::cout << "Enter your choice (1-3): ";

        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            BinaryTree<char> letters = wordMap.keySet();
            std::cout << "Letters in the file: ";
            letters.printInOrder();
            std::cout << std::endl;
        }
        else if (choice == 2) {
            std::cout << "Enter a letter: ";
            char letter;
            std::cin >> letter;
            std::cin.ignore();

            letter = static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));

            BinaryTree<std::string>* wordSet = wordMap.get(letter);

            if (wordSet != nullptr) {
                std::cout << "Words starting with '" << letter << "': ";
                wordSet->printInOrder();
                std::cout << std::endl;
            }
            else {
                std::cout << "No words found starting with '" << letter << "'." << std::endl;
            }
        }
        else if (choice == 3) {
            std::cout << "Returning to Main Menu." << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please select 1, 2, or 3." << std::endl;
        }
    }
}
