#pragma once
#include <string>
#include <vector>
#include <optional>
#include "LibrarySystem.h"

class User : public LibrarySystem {
private:
    std::string name;
    std::string studentId;
    std::string password;

    // Authenticate a user by reading name, studentId, and password and checking userInfo.txt
    bool authenticate();
    // Check if a user with given name and studentId already exists
    bool userExists(const std::string &name, const std::string &sid);
    // Find a book by its numeric ID from systemBooks.txt
    std::optional<Book> findBookById(int id);
    // Find a book by its exact title from systemBooks.txt
    std::optional<Book> findBookByTitle(const std::string &title);

public:
    // Register a new user into userInfo.txt (ensures unique student ID for the given name)
    void addUser();
    // Borrow a book (authenticates user, searches for book, logs to borrowerInfo.txt and removes from systemBooks.txt)
    void borrowBook();
    // Return a borrowed book (authenticates user, shows only user's records to select, restores to systemBooks.txt)
    void returnBook();
    // Search book by prompting user to choose ID or Title (polymorphic dispatcher)
    void findBook(); // polymorphic dispatcher (ask user for id or title)
    // User menu loop
    void showMenu() override;
};
