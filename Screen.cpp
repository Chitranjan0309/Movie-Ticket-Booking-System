// Screen.cpp
// Single responsibility: one auditorium. Owns the physical Seat objects.
// Knows: screen number, its own seats.
// Does: lets other classes read its seat list.
// Must NOT do: know about movies, shows or bookings.
#ifndef CINEMA_SCREEN_INCLUDED
#define CINEMA_SCREEN_INCLUDED

#include <vector>
#include "Seat.cpp"
using std::vector;

class Screen {
private:
    int screenNumber;
    vector<Seat*> seats;    // Composition: seats belong to this screen only

public:
    explicit Screen(int screenNumber) : screenNumber(screenNumber) {}

    // destructor: composition means Screen owns and frees its Seats
    ~Screen() {
        for (Seat* s : seats) delete s;
    }

    void addSeat(Seat* seat) { seats.push_back(seat); }

    const vector<Seat*>& getSeats() const { return seats; }
    int getScreenNumber() const { return screenNumber; }
};

#endif
