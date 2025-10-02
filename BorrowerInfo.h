#pragma once
#include <string>
#include <iostream>

class BorrowerInfo {
public:
    std::string borrowerName;
    std::string studentId;
    int bookId{};
    std::string bookName;
    std::string category;

    BorrowerInfo() = default;
    BorrowerInfo(const std::string &bn, const std::string &sid, int bid, const std::string &bname, const std::string &cat)
        : borrowerName(bn), studentId(sid), bookId(bid), bookName(bname), category(cat) {}

    void displayInfo() const;
};
