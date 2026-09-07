// TicketPrinter.cpp
// Single responsibility: format and print a ticket (F7). Printing ONLY.
// Knows: nothing (stateless) - it only reads a Booking passed to it.
// Does: prints booking id, movie, screen, time, seat numbers, total amount.
// Must NOT do: change the booking's status or calculate the price itself.
#ifndef CINEMA_TICKETPRINTER_INCLUDED
#define CINEMA_TICKETPRINTER_INCLUDED

#include <iostream>
#include <iomanip>
#include "Booking.cpp"
using std::cout;
using std::endl;

class TicketPrinter {
public:
    static void printTicket(Booking* booking) {
        Show* show = booking->getShow();
        cout << "\n================ TICKET ================\n";
        cout << "Booking Id : " << booking->getBookingId() << "\n";
        cout << "Movie      : " << show->getMovie()->getTitle() << "\n";
        cout << "Screen     : " << show->getScreen()->getScreenNumber() << "\n";
        cout << "Time       : " << show->getStartTime() << "\n";
        cout << "Seats      : ";
        const vector<ShowSeat*>& seats = booking->getBookedSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeat()->getSeatNumber();
            if (i + 1 < seats.size()) cout << ", ";
        }
        cout << "\nAmount     : Rs. " << std::fixed << std::setprecision(2)
             << booking->getTotalAmount() << "\n";
        cout << "==========================================\n";
    }
};

#endif
