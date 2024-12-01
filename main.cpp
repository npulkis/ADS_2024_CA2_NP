#include <iostream>
#include "WordOrganizer.h"

int main() {
    int choice = 0;
    while (choice != 2) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Word Organizer\n";
        std::cout << "2. Exit\n";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            WordOrganizer wordOrganizer;
            wordOrganizer.run();
        }
        else if (choice == 2) {
            std::cout << "Exiting the program." << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please select 1 or 2." << std::endl;
        }
    }

    return 0;
}
