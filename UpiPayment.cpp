// UpiPayment.cpp
// Single responsibility: actually process a UPI payment.
// Knows: the UPI id used for this transaction.
// Does: validates the UPI id format and "charges" the amount.
// Must NOT do: know about Booking, Show or Seat.
#ifndef CINEMA_UPIPAYMENT_INCLUDED
#define CINEMA_UPIPAYMENT_INCLUDED

#include <string>
#include "Payment.cpp"
using std::string;

class UpiPayment : public Payment {           // Inheritance
private:
    string upiId;

public:
    explicit UpiPayment(const string& upiId) : upiId(upiId) {}

    // Runtime polymorphism: called through a Payment* / Payment&
    bool pay(double amountToPay) override {
        amount = amountToPay;
        bool isValidUpiId = upiId.find('@') != string::npos;   // e.g. "name@bank"
        bool isValidAmount = amountToPay > 0;
        return isValidUpiId && isValidAmount;
    }
};

#endif
