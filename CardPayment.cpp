// CardPayment.cpp
// Single responsibility: actually process a card payment.
// Knows: the card number used for this transaction.
// Does: validates the card number and "charges" the amount.
// Must NOT do: know about Booking, Show or Seat.
#ifndef CINEMA_CARDPAYMENT_INCLUDED
#define CINEMA_CARDPAYMENT_INCLUDED

#include <string>
#include "Payment.cpp"
using std::string;

class CardPayment : public Payment {           // Inheritance
private:
    string cardNumber;

public:
    explicit CardPayment(const string& cardNumber) : cardNumber(cardNumber) {}

    bool pay(double amountToPay) override {    // Runtime polymorphism
        amount = amountToPay;
        bool isValidCardNumber = cardNumber.size() == 16;
        bool isValidAmount = amountToPay > 0;
        return isValidCardNumber && isValidAmount;
    }
};

#endif
