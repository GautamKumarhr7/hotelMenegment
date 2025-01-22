#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
public:
    std::string name;
    std::string email;

    Customer(const std::string &name, const std::string &email);
};

#endif
