#include <iostream>
#include "WordOrganizer.h"
#include "DataViewer.h"


int main() {
    int choice = 0;
    while (choice != 3) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Word Organizer\n";
        std::cout << "2. DataViewer\n";
        std::cout << "3. Exit\n";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            WordOrganizer wordOrganizer;
            wordOrganizer.run();
        }
        else if (choice == 2) {
            DataViewer dataViewer;
            dataViewer.run();
        }
        else if (choice == 3) {
            std::cout << "Exiting the program." << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please select 1, 2 or 3." << std::endl;
        }
    }

    return 0;
}
