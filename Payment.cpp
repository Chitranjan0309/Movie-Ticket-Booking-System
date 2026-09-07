// Payment.cpp
// Abstraction: the payment CONTRACT every payment method must honour.
// Knows: nothing about cinemas, bookings or seats - only "an amount was
//        attempted" (kept as a protected field for subclasses to use/log).
// Does: declares the pure virtual pay() - no implementation here.
// Must NOT do: contain any concrete payment logic (that belongs in the
//              subclasses) and must NOT be instantiated directly.
#ifndef CINEMA_PAYMENT_INCLUDED
#define CINEMA_PAYMENT_INCLUDED

class Payment {
protected:
    double amount = 0.0;

public:
    // Abstraction: pure virtual method -> Payment is an abstract class.
    virtual bool pay(double amount) = 0;

    // virtual destructor: required because we delete Payment* polymorphically
    virtual ~Payment() {}
};

#endif
