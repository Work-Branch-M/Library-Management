# Library Information System (LIS)

A simple C++ console-based Library Information System using text files for persistent storage.

## Features
- Administrator (Manager)
  - Login using `ManagerData.txt`
  - Add/Remove books in `systemBooks.txt`
  - View borrowing records from `borrowerInfo.txt`
- General User (Student)
  - Register in `userInfo.txt`
  - Login (name + student ID + password)
  - Borrow/Return books (updates `systemBooks.txt` and `borrowerInfo.txt`)
  - Search book by ID or Title
  - View all books sorted by ID

## File Formats
- `ManagerData.txt`
  - `username,password,`
  - Example:
    ```
    admin1,12345,
    admin2,password,
    ```
- `systemBooks.txt`
  - `bookId,title,category`
  - Example:
    ```
    101,The Great Gatsby,Fiction
    102,Data Structures,Education
    ```
- `userInfo.txt`
  - `name,studentId,password`
  - Example:
    ```
    John,2023001,pass123
    Alice,2023002,hello456
    ```
- `borrowerInfo.txt`
  - `name,studentId,bookId,title,category`

## Build (Windows, g++)
1. Open a terminal (PowerShell or CMD) in the project folder `Library management/`.
2. Compile:
   ```bash
   g++ -std=c++17 -O2 -o LIS.exe main.cpp BookManager.cpp User.cpp BorrowerInfo.cpp
   ```
3. Run:
   ```bash
   .\LIS.exe
   ```

If `g++` is not recognized, install MinGW-w64 (or use MSYS2) and ensure `g++` is in your PATH.

## Usage
- Start the program and choose your role:
  - `Administrator (Manager)` to manage books and view borrowing info.
  - `General User (Student)` to register, borrow/return, search, and view books.
- Sample credentials are included for quick testing.
- The app creates the required `.txt` files if they are missing.

## Notes
- The system uses exact-title match for title search.
- All data is stored in plain text; avoid commas in names/titles to keep the CSV simple.
- You can pre-populate `systemBooks.txt` and `ManagerData.txt` as needed.
