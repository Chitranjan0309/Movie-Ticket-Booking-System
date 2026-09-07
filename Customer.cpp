// Customer.cpp
// Single responsibility: identify the person making a booking.
// Knows: name, phone.
// Does: nothing else - deliberately kept tiny.
// Must NOT do: hold booking history (Booking references Customer, not the
//              other way round, so Customer stays reusable and independent).
#ifndef CINEMA_CUSTOMER_INCLUDED
#define CINEMA_CUSTOMER_INCLUDED

#include <string>
using std::string;

class Customer {
private:
    string name;
    string phone;

public:
    Customer(const string& name, const string& phone)
        : name(name), phone(phone) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
};

#endif
