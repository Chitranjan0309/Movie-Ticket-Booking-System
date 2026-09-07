// CashPayment.cpp
// Single responsibility: actually process a cash payment at the counter.
// Knows: nothing extra - cash needs no account details.
// Does: "charges" the amount (cash only fails on a non-positive amount).
// Must NOT do: know about Booking, Show or Seat.
#ifndef CINEMA_CASHPAYMENT_INCLUDED
#define CINEMA_CASHPAYMENT_INCLUDED

#include "Payment.cpp"

class CashPayment : public Payment {           // Inheritance
public:
    bool pay(double amountToPay) override {    // Runtime polymorphism
        amount = amountToPay;
        return amountToPay > 0;
    }
};

#endif
