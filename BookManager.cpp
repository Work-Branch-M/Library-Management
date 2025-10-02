#include "BookManager.h"
#include <iostream>
#include <iomanip>

bool BookManager::managerLogin() {
    std::string uname, pass;
    std::cout << "Manager username: ";
    std::getline(std::cin, uname);
    std::cout << "Password: ";
    std::getline(std::cin, pass);

    std::ifstream in(managerFile);
    if (!in.is_open()) {
        std::cout << "Could not open " << managerFile << ". Ensure the file exists." << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;
        auto parts = splitCSV(line);
        if (parts.size() >= 2) {
            if (parts[0] == uname && parts[1] == pass) return true;
        }
    }
    std::cout << "Invalid manager credentials." << std::endl;
    return false;
}

void BookManager::addBook() {
    auto books = loadBooks();
    Book b;
    std::cout << "Enter new Book ID: ";
    std::string idStr; std::getline(std::cin, idStr);
    try { b.id = std::stoi(trim(idStr)); } catch(...) { std::cout << "Invalid ID." << std::endl; return; }
    for (const auto &x : books) {
        if (x.id == b.id) { std::cout << "Book ID already exists." << std::endl; return; }
    }
    std::cout << "Enter Book Title: ";
    std::getline(std::cin, b.title);
    std::cout << "Enter Category: ";
    std::getline(std::cin, b.category);
    books.push_back(b);
    saveBooks(books);
    std::cout << "Book added successfully." << std::endl;
}

void BookManager::removeBook() {
    auto books = loadBooks();
    std::cout << "Enter Book ID to remove: ";
    std::string idStr; std::getline(std::cin, idStr);
    int id{}; try { id = std::stoi(trim(idStr)); } catch(...) { std::cout << "Invalid ID." << std::endl; return; }
    auto it = std::remove_if(books.begin(), books.end(), [&](const Book &b){return b.id == id;});
    if (it == books.end()) {
        std::cout << "No book with that ID found." << std::endl;
        return;
    }
    books.erase(it, books.end());
    saveBooks(books);
    std::cout << "Book removed." << std::endl;
}

void BookManager::viewBorrowedBooks() {
    std::ifstream in(borrowersFile);
    if (!in.is_open()) {
        std::cout << "No borrowing records found." << std::endl;
        return;
    }
    std::cout << "\n--- Borrowing Records ---\n";
    // Header
    std::cout << std::left
              << std::setw(20) << "Name"
              << std::setw(15) << "Student ID"
              << std::setw(8)  << "BookID"
              << std::setw(30) << "Title"
              << std::setw(20) << "Category" << "\n";
    std::cout << std::string(93, '-') << "\n";
    std::string line;
    bool any = false;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;
        auto p = splitCSV(line);
        if (p.size() >= 5) {
            any = true;
            BorrowerInfo bi(p[0], p[1], std::stoi(p[2]), p[3], p[4]);
            bi.displayInfo();
        }
    }
    if (!any) std::cout << "No records." << std::endl;
    std::cout << "--------------------------\n";
}

void BookManager::showMenu() {
    if (!managerLogin()) return;
    while (true) {
        std::cout << "\n-- Manager Menu --\n";
        std::cout << "1. Add Book\n2. Remove Book\n3. View Borrowing Info\n4. View All Books\n0. Logout\nChoose: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") addBook();
        else if (choice == "2") removeBook();
        else if (choice == "3") viewBorrowedBooks();
        else if (choice == "4") displayAllBooksSorted();
        else if (choice == "0") break;
        else std::cout << "Invalid choice." << std::endl;
    }
}
