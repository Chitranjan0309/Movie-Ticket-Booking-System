// PriceCalculator.cpp
// Single responsibility: turn a list of seats into a total amount (F5).
// Knows: nothing (stateless) - it only reads Seat::getPrice().
// Does: sums prices; provides an overload for a single seat too.
// Must NOT do: know about Booking, Payment or Show.
#ifndef CINEMA_PRICECALCULATOR_INCLUDED
#define CINEMA_PRICECALCULATOR_INCLUDED

#include <vector>
#include "ShowSeat.cpp"
using std::vector;

class PriceCalculator {
public:
    // Compile-time polymorphism: two calculateTotal() overloads.
    static double calculateTotal(const vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (ShowSeat* seat : seats) {
            total += calculateTotal(seat);        // calls the single-seat overload
        }
        return total;
    }

    static double calculateTotal(ShowSeat* seat) {
        return seat->getSeat()->getPrice();
    }
};

#endif
