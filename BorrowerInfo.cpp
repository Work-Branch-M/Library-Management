#include "BorrowerInfo.h"

void BorrowerInfo::displayInfo() const {
    std::cout << borrowerName << " (" << studentId << ") -> "
              << bookId << ": " << bookName << " [" << category << "]\n";
}
