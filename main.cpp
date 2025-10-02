#include <iostream>
#include <fstream>
#include "BookManager.h"
#include "User.h"
#include "LibrarySystem.h" // Added include for LibrarySystem

static void ensureFiles() {
    // Create empty files if they don't exist
    const char* files[] = {"ManagerData.txt", "systemBooks.txt", "userInfo.txt", "borrowerInfo.txt"};
    for (auto f : files) {
        std::ifstream in(f);
        if (!in.good()) {
            std::ofstream out(f); // create
        }
    }
}

int main() {
    ensureFiles();
    while (true) {
        std::cout << "\n==== Library Information System ====\n";
        std::cout << "1. Administrator (Manager)\n2. General User (Student)\n3. Developer Info\n0. Exit\nChoose: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") {
            // Manager flow
            BookManager m; m.showMenu();
        } else if (choice == "2") {
            // User flow
            User u; u.showMenu();
        } else if (choice == "3") {
            // Centralized developer info
            LibrarySystem::showDeveloperInfo();
        } else if (choice == "0") {
            std::cout << "Goodbye!" << std::endl; break;
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    return 0;
}
