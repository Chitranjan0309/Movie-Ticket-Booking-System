// Seat.cpp
// Single responsibility: one physical seat - its number and category.
// Knows: seat number, seat type.
// Does: reports its own price via the shared price table.
// Must NOT do: know whether it is booked for a particular show
//              (that belongs to ShowSeat, not Seat).
#ifndef CINEMA_SEAT_INCLUDED
#define CINEMA_SEAT_INCLUDED

#include <string>
#include "Common.cpp"
using std::string;

class Seat {
private:
    string seatNumber;   // e.g. "A1"
    SeatType type;

public:
    Seat(const string& seatNumber, SeatType type)
        : seatNumber(seatNumber), type(type) {}

    string getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }

    // Abstraction over the pricing rule -> caller never hard-codes a price.
    double getPrice() const { return priceForSeatType(type); }
};

#endif
