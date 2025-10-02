#pragma once
#include <string>
#include <vector>
#include "LibrarySystem.h"
#include "BorrowerInfo.h"

class BookManager : public LibrarySystem {
public:
    bool managerLogin();
    void addBook();
    void removeBook();
    void viewBorrowedBooks();
    void showMenu() override;
};
