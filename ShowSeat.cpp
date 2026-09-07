// ShowSeat.cpp
// Single responsibility: the AVAILABLE/BOOKED status of ONE seat FOR ONE show.
// This is the class that actually answers "seat layout" (F3) - a Seat by
// itself has no notion of being booked; only a ShowSeat does.
// Knows: which physical Seat it wraps, its own status.
// Does: validated transitions between AVAILABLE and BOOKED.
// Must NOT do: decide price (PriceCalculator's job) or print anything.
#ifndef CINEMA_SHOWSEAT_INCLUDED
#define CINEMA_SHOWSEAT_INCLUDED

#include "Seat.cpp"
#include "Common.cpp"
#include <stdexcept>

class ShowSeat {
private:
    Seat* seat;                                 // association: refers to a real Seat
    SeatStatus status = SeatStatus::AVAILABLE;   // private -> only changed through book()/release()

public:
    explicit ShowSeat(Seat* seat) : seat(seat) {}

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    // Encapsulation: seatStatus can only change through these validated methods,
    // never assigned directly from outside the class.
    void book() {
        if (status == SeatStatus::BOOKED) {
            throw std::runtime_error("Seat " + seat->getSeatNumber() + " is already booked");
        }
        status = SeatStatus::BOOKED;
    }

    void release() { status = SeatStatus::AVAILABLE; }

    Seat* getSeat() const { return seat; }
};

#endif
