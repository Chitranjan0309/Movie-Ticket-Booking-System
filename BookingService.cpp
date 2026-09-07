// BookingService.cpp
// Single responsibility: ORCHESTRATE the booking flow end to end. It does
// not do any single job itself - it calls Show, ShowSeat, PriceCalculator,
// Booking, Payment and TicketPrinter in the right order (see the sequence
// diagram, Step F, for exactly this call sequence).
// Knows: the cinema, the shows on offer, the bookings made so far.
// Does: F1-F8 orchestration.
// Must NOT do: contain seat-availability logic, pricing logic or payment
//              logic itself - those stay in their own classes (SRP).
#ifndef CINEMA_BOOKINGSERVICE_INCLUDED
#define CINEMA_BOOKINGSERVICE_INCLUDED

#include <vector>
#include <set>
#include <iostream>
#include <stdexcept>
#include "Cinema.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
using std::vector;
using std::cout;
using std::endl;

class BookingService {
private:
    Cinema* cinema;
    vector<Show*> shows;         // shows on offer (BookingService owns these)
    vector<Booking*> bookings;   // all bookings made through this service

public:
    explicit BookingService(Cinema* cinema) : cinema(cinema) {}

    ~BookingService() {
        for (Booking* b : bookings) delete b;
        for (Show* s : shows) delete s;
    }

    void addShow(Show* show) { shows.push_back(show); }

    // F1: list all movies currently playing (derived from the shows on offer)
    void listMovies() const {
        std::set<string> seenTitles;
        cout << "\n----- Movies now playing -----\n";
        for (Show* show : shows) {
            const string& title = show->getMovie()->getTitle();
            if (seenTitles.insert(title).second) {
                cout << "  " << title << " (" << show->getMovie()->getLanguage()
                     << ", " << show->getMovie()->getDurationMinutes() << " min)\n";
            }
        }
    }

    // F2: for a chosen movie, list its shows (screen + start time)
    vector<Show*> listShows(const string& movieTitle) const {
        vector<Show*> matches;
        cout << "\n----- Shows for \"" << movieTitle << "\" -----\n";
        for (Show* show : shows) {
            if (show->getMovie()->getTitle() == movieTitle) {
                matches.push_back(show);
                cout << "  [" << show->getShowId() << "] Screen "
                     << show->getScreen()->getScreenNumber()
                     << " at " << show->getStartTime() << "\n";
            }
        }
        return matches;
    }

    Booking* findBookingById(int bookingId) const {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) return b;
        }
        return nullptr;
    }

    Show* findShowById(int showId) const {
        for (Show* show : shows) {
            if (show->getShowId() == showId) return show;
        }
        return nullptr;
    }

    // F3: display seat layout for a chosen show
    void showSeatLayout(Show* show) const {
        show->printSeatLayout();
    }

    // F4 + F5: book seats for a show and price the booking. Returns a
    // PENDING booking, or throws if any seat is unavailable/invalid.
    Booking* bookSeats(Show* show, Customer* customer, const vector<string>& seatNumbers) {
        vector<ShowSeat*> chosenSeats;

        for (const string& seatNumber : seatNumbers) {
            ShowSeat* found = nullptr;
            for (ShowSeat* ss : show->getShowSeats()) {
                if (ss->getSeat()->getSeatNumber() == seatNumber) {
                    found = ss;
                    break;
                }
            }
            if (found == nullptr) {
                throw std::runtime_error("Invalid seat number: " + seatNumber);
            }
            if (!found->isAvailable()) {
                throw std::runtime_error("Seat " + seatNumber + " is already booked");
            }
            chosenSeats.push_back(found);
        }

        // Only reserve seats after every seat in the request passed validation,
        // so a partially-invalid request changes nothing (edge case 1).
        for (ShowSeat* seat : chosenSeats) {
            seat->book();
        }

        double total = PriceCalculator::calculateTotal(chosenSeats);
        Booking* booking = new Booking(show, customer, chosenSeats, total);
        bookings.push_back(booking);
        return booking;
    }

    // F6: pay for a booking. A failed payment must NOT confirm the booking,
    // and the seats it was holding are released back to AVAILABLE.
    bool makePayment(Booking* booking, Payment& payment) {
        bool paymentSucceeded = payment.pay(booking->getTotalAmount());
        if (paymentSucceeded) {
            booking->confirm();
            TicketPrinter::printTicket(booking);
        } else {
            for (ShowSeat* seat : booking->getBookedSeats()) {
                seat->release();
            }
            booking->cancel();
            cout << "\nPayment failed. Booking " << booking->getBookingId()
                 << " was NOT confirmed; seats are available again.\n";
        }
        return paymentSucceeded;
    }

    // F8: cancel a booking - its seats become AVAILABLE again
    void cancelBooking(Booking* booking) {
        booking->cancel();
        cout << "\nBooking " << booking->getBookingId() << " cancelled. "
             << "Seats are AVAILABLE again.\n";
    }
};

#endif
