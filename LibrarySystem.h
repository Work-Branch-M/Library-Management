#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

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
        for (const auto &b : books) {
            std::cout << b.id << " | " << b.title << " | " << b.category << "\n";
        }
        if (books.empty()) {
            std::cout << "No books available." << std::endl;
        }
        std::cout << "-----------------------------------\n";
    }
};
