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

    bool authenticate();
    bool userExists(const std::string &name, const std::string &sid);
    std::optional<Book> findBookById(int id);
    std::optional<Book> findBookByTitle(const std::string &title);

public:
    void addUser();
    void borrowBook();
    void returnBook();
    void findBook(); // polymorphic dispatcher (ask user for id or title)
    void showMenu() override;
};
