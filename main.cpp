#include <iostream>
#include <fstream>
#include "BookManager.h"
#include "User.h"

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
            BookManager m; m.showMenu();
        } else if (choice == "2") {
            User u; u.showMenu();
        } else if (choice == "3") {
            std::cout << "Developed by: Your Group Name / Students\n";
            std::cout << "Members: Name1 (ID), Name2 (ID)\n";
        } else if (choice == "0") {
            std::cout << "Goodbye!" << std::endl; break;
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    return 0;
}
