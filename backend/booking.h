#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
public:
    int roomNumber;
    std::string customerName;
    std::string customerEmail;

    Booking(int roomNumber, const std::string &customerName, const std::string &customerEmail);
};

#endif
