#include "BorrowerInfo.h"
#include <iomanip>

void BorrowerInfo::displayInfo() const {
    using std::left; using std::setw;
    std::cout << left
              << setw(20) << borrowerName
              << setw(15) << studentId
              << setw(8)  << bookId
              << setw(30) << bookName.substr(0,29)
              << setw(20) << category.substr(0,19)
              << "\n";
}
