#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

struct Book {
    int id{};
    std::string title;
    std::string category;
};

class LibrarySystem {
protected:
    // File paths
    std::string managerFile = "ManagerData.txt";
    std::string booksFile = "systemBooks.txt";
    std::string usersFile = "userInfo.txt";
    std::string borrowersFile = "borrowerInfo.txt";

    static inline std::string trim(const std::string &s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    static inline std::vector<std::string> splitCSV(const std::string &line) {
        std::vector<std::string> out;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ',')) {
            out.push_back(trim(item));
        }
        return out;
    }

    static inline bool fileExists(const std::string &path) {
        std::ifstream f(path);
        return f.good();
    }

    // Load all books from systemBooks.txt
    std::vector<Book> loadBooks() const {
        std::vector<Book> books;
        std::ifstream in(booksFile);
        std::string line;
        while (std::getline(in, line)) {
            line = trim(line);
            if (line.empty()) continue;
            auto parts = splitCSV(line);
            if (parts.size() >= 3) {
                try {
                    Book b{std::stoi(parts[0]), parts[1], parts[2]};
                    books.push_back(b);
                } catch (...) {
                    // skip malformed lines
                }
            }
        }
        return books;
    }

    // Save all books to systemBooks.txt
    void saveBooks(const std::vector<Book> &books) const {
        std::ofstream out(booksFile, std::ios::trunc);
        for (const auto &b : books) {
            out << b.id << "," << b.title << "," << b.category << "\n";
        }
    }

public:
    virtual ~LibrarySystem() = default;
    virtual void showMenu() = 0;

    // Utility to display all books sorted by ID
    void displayAllBooksSorted() {
        auto books = loadBooks();
        std::sort(books.begin(), books.end(), [](const Book &a, const Book &b){return a.id < b.id;});
        std::cout << "\n----- All Books (sorted by ID) -----\n";
        std::cout << std::left
                  << std::setw(8) << "ID"
                  << std::setw(30) << "Title"
                  << std::setw(20) << "Category" << "\n";
        std::cout << std::string(58, '-') << "\n";
        for (const auto &b : books) {
            std::cout << std::left
                      << std::setw(8) << b.id
                      << std::setw(30) << b.title.substr(0,29)
                      << std::setw(20) << b.category.substr(0,19) << "\n";
        }
        if (books.empty()) {
            std::cout << "No books available." << std::endl;
        }
        std::cout << "-----------------------------------\n";
    }

    // Print developer/participants information (edit with your real data)
    static void showDeveloperInfo() {
        std::cout << "\n==== Developer Information ====\n";
        std::cout << std::left
                  << std::setw(20) << "Name"
                  << std::setw(15) << "Student ID"
                  << std::setw(18) << "Contact"
                  << std::setw(22) << "Completion Time" << "\n";
        std::cout << std::string(75, '-') << "\n";
        // TODO: Replace with your group's real info
        std::cout << std::setw(20) << "John Doe"
                  << std::setw(15) << "2023XXXX"
                  << std::setw(18) << "+8801XXXXXXXX"
                  << std::setw(22) << "2025-10-02 19:27" << "\n";
        std::cout << std::setw(20) << "Alice Smith"
                  << std::setw(15) << "2023YYYY"
                  << std::setw(18) << "+8801YYYYYYYY"
                  << std::setw(22) << "2025-10-02 19:27" << "\n";
        std::cout << std::string(75, '-') << "\n";
    }
};
