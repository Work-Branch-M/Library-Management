#include "User.h"
#include <iostream>
#include <fstream>

bool User::userExists(const std::string &nm, const std::string &sid) {
    std::ifstream in(usersFile);
    if (!in.is_open()) return false;
    std::string line;
    while (std::getline(in, line)) {
        auto p = splitCSV(line);
        if (p.size() >= 3) {
            if (p[0] == nm && p[1] == sid) return true;
        }
    }
    return false;
}

bool User::authenticate() {
    std::cout << "Name: "; std::getline(std::cin, name);
    std::cout << "Student ID: "; std::getline(std::cin, studentId);
    std::cout << "Password: "; std::getline(std::cin, password);

    std::ifstream in(usersFile);
    if (!in.is_open()) {
        std::cout << "No users registered yet." << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(in, line)) {
        auto p = splitCSV(line);
        if (p.size() >= 3) {
            if (p[0] == name && p[1] == studentId && p[2] == password) return true;
        }
    }
    std::cout << "Invalid credentials." << std::endl;
    return false;
}

void User::addUser() {
    std::string nm, sid, pass;
    std::cout << "Enter Name: "; std::getline(std::cin, nm);
    std::cout << "Enter Student ID: "; std::getline(std::cin, sid);
    std::cout << "Enter Password: "; std::getline(std::cin, pass);

    if (userExists(nm, sid)) {
        std::cout << "User with this ID already exists." << std::endl;
        return;
    }
    std::ofstream out(usersFile, std::ios::app);
    out << nm << "," << sid << "," << pass << "\n";
    std::cout << "Registration successful." << std::endl;
}

std::optional<Book> User::findBookById(int id) {
    auto books = loadBooks();
    for (const auto &b : books) if (b.id == id) return b;
    return std::nullopt;
}

std::optional<Book> User::findBookByTitle(const std::string &title) {
    auto books = loadBooks();
    for (const auto &b : books) if (b.title == title) return b;
    return std::nullopt;
}

void User::borrowBook() {
    if (!authenticate()) return;

    std::cout << "Search by (1) ID or (2) Title? ";
    std::string c; std::getline(std::cin, c);
    std::optional<Book> found;
    if (c == "1") {
        std::cout << "Enter Book ID: ";
        std::string idStr; std::getline(std::cin, idStr);
        try { found = findBookById(std::stoi(trim(idStr))); } catch(...) {}
    } else if (c == "2") {
        std::string t; std::cout << "Enter Title: "; std::getline(std::cin, t);
        found = findBookByTitle(t);
    }

    if (!found) { std::cout << "Book not found or not available." << std::endl; return; }

    // Append to borrowerInfo
    std::ofstream bout(borrowersFile, std::ios::app);
    bout << name << "," << studentId << "," << found->id << "," << found->title << "," << found->category << "\n";

    // Remove from systemBooks
    auto books = loadBooks();
    books.erase(std::remove_if(books.begin(), books.end(), [&](const Book &b){return b.id == found->id;}), books.end());
    saveBooks(books);

    std::cout << "Borrow successful." << std::endl;
}

void User::returnBook() {
    if (!authenticate()) return;

    // Load borrower records and find this user's borrowed items
    std::ifstream in(borrowersFile);
    if (!in.is_open()) { std::cout << "No borrow records." << std::endl; return; }
    std::vector<std::vector<std::string>> rows; std::string line; bool has=false;
    while (std::getline(in, line)) {
        auto p = splitCSV(line);
        if (p.size() >= 5) {
            rows.push_back(p);
            if (p[0]==name && p[1]==studentId) has=true;
        }
    }
    if (!has) { std::cout << "You have no borrowed books." << std::endl; return; }

    std::cout << "Your borrowed books:" << std::endl;
    for (size_t i=0;i<rows.size();++i) {
        auto &p = rows[i];
        if (p[0]==name && p[1]==studentId) {
            std::cout << i+1 << ". " << p[2] << " - " << p[3] << " [" << p[4] << "]\n";
        }
    }
    std::cout << "Enter the number to return: ";
    std::string idxStr; std::getline(std::cin, idxStr); int idx{};
    try { idx = std::stoi(trim(idxStr)); } catch(...) { std::cout << "Invalid input." << std::endl; return; }
    if (idx<1 || idx>(int)rows.size()) { std::cout << "Out of range." << std::endl; return; }

    auto p = rows[idx-1];
    if (!(p[0]==name && p[1]==studentId)) { std::cout << "Selected entry is not yours." << std::endl; return; }

    // Re-add to systemBooks
    auto books = loadBooks();
    Book b{std::stoi(p[2]), p[3], p[4]};
    // Ensure not duplicate
    bool exists=false; for (const auto &x:books) if (x.id==b.id) exists=true;
    if (!exists) books.push_back(b);
    saveBooks(books);

    // Remove from borrowerInfo.txt by index (maintain others)
    std::ofstream out(borrowersFile, std::ios::trunc);
    for (size_t i=0;i<rows.size();++i) {
        if (i==idx-1) continue; // skip returned
        auto &r = rows[i];
        if (r.size()>=5)
            out << r[0] << "," << r[1] << "," << r[2] << "," << r[3] << "," << r[4] << "\n";
    }

    std::cout << "Return successful." << std::endl;
}

void User::findBook() {
    std::cout << "Search by (1) ID or (2) Title? ";
    std::string c; std::getline(std::cin, c);
    if (c == "1") {
        std::cout << "Enter Book ID: ";
        std::string idStr; std::getline(std::cin, idStr);
        try {
            auto res = findBookById(std::stoi(trim(idStr)));
            if (res) std::cout << res->id << " | " << res->title << " | " << res->category << "\n";
            else std::cout << "Not found." << std::endl;
        } catch(...) { std::cout << "Invalid ID." << std::endl; }
    } else if (c == "2") {
        std::string t; std::cout << "Enter Title: "; std::getline(std::cin, t);
        auto res = findBookByTitle(t);
        if (res) std::cout << res->id << " | " << res->title << " | " << res->category << "\n";
        else std::cout << "Not found." << std::endl;
    } else {
        std::cout << "Invalid choice." << std::endl;
    }
}

void User::showMenu() {
    while (true) {
        std::cout << "\n-- User Menu --\n";
        std::cout << "1. Register\n2. Borrow Book\n3. Return Book\n4. View All Books\n5. Search Book\n0. Back\nChoose: ";
        std::string choice; std::getline(std::cin, choice);
        if (choice == "1") addUser();
        else if (choice == "2") borrowBook();
        else if (choice == "3") returnBook();
        else if (choice == "4") displayAllBooksSorted();
        else if (choice == "5") findBook();
        else if (choice == "0") break;
        else std::cout << "Invalid choice." << std::endl;
    }
}
