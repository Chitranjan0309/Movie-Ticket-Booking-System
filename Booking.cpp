// Booking.cpp
// Single responsibility: represent ONE booking record and its own status
// transitions (PENDING -> CONFIRMED -> CANCELLED). It does NOT decide seat
// availability, price or how payment happens - it just records the result.
// Knows: which show, which customer, which seats, the total, its status.
// Does: confirm()/cancel() with their own validated state changes.
// Must NOT do: print a ticket (TicketPrinter's job) or talk to Payment
//              objects directly (BookingService orchestrates that).
#ifndef CINEMA_BOOKING_INCLUDED
#define CINEMA_BOOKING_INCLUDED

#include <vector>
#include "Show.cpp"
#include "Customer.cpp"
#include "ShowSeat.cpp"
#include "Common.cpp"
using std::vector;

class Booking {
private:
    int bookingId;
    Show* show;
    Customer* customer;
    vector<ShowSeat*> bookedSeats;   // aggregation: seats belong to the Show
    double totalAmount;
    BookingStatus status;

    static int nextBookingId;        // Static member: generates unique ids

public:
    Booking(Show* show, Customer* customer, const vector<ShowSeat*>& bookedSeats, double totalAmount)
        : show(show), customer(customer), bookedSeats(bookedSeats),
          totalAmount(totalAmount), status(BookingStatus::PENDING) {
        bookingId = nextBookingId++;   // `this` not needed here, but used below
    }

    void confirm() {
        if (status != BookingStatus::PENDING) {
            throw std::runtime_error("Only a PENDING booking can be confirmed");
        }
        this->status = BookingStatus::CONFIRMED;
    }

    // F8: cancel a booking - seats become AVAILABLE again
    void cancel() {
        if (status == BookingStatus::CANCELLED) return;
        for (ShowSeat* seat : bookedSeats) {
            seat->release();
        }
        this->status = BookingStatus::CANCELLED;
    }

    int getBookingId() const { return bookingId; }
    Show* getShow() const { return show; }
    Customer* getCustomer() const { return customer; }
    const vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }
};

int Booking::nextBookingId = 1001;   // definition of the static member

#endif
