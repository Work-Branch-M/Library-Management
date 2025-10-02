#pragma once
#include <string>
#include <vector>
#include "LibrarySystem.h"
#include "BorrowerInfo.h"

class BookManager : public LibrarySystem {
public:
    // Verify manager credentials from ManagerData.txt
    bool managerLogin();
    // Add a new book to systemBooks.txt (requires unique ID)
    void addBook();
    // Remove an existing book by ID from systemBooks.txt
    void removeBook();
    // Print all borrowing records from borrowerInfo.txt
    void viewBorrowedBooks();
    // Manager menu loop
    void showMenu() override;
};
