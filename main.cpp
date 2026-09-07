// main.cpp
// Course rule: "no header files" -> every class's declaration+definition
// lives in its own .cpp, and this file #includes them in dependency order
// so the whole program is compiled as a single translation unit.
//
// Run modes:
//   ./cinema           -> interactive console menu (normal use)
//   ./cinema --demo    -> scripted run that exercises every edge case
//                         (F1-F8 + the 4 required edge cases) with no
//                         keyboard input, for the assignment demo/screenshot.

#include "Common.cpp"
#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "Booking.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"
#include "CinemaMenu.cpp"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// Builds a small cinema: 1 cinema, 2 screens, a handful of seats each.
// cinemaOut / moviesOut let the caller take ownership and free them when
// done - Show only aggregates Movie (Step D: aggregation, not composition),
// so movies must be owned somewhere else, here the catalog vector in main().
BookingService* buildDemoCinema(Cinema*& cinemaOut, vector<Movie*>& moviesOut) {
    Cinema* cinema = new Cinema("PVR Sohna");
    cinemaOut = cinema;

    Screen* screen1 = new Screen(1);
    screen1->addSeat(new Seat("A1", SeatType::SILVER));
    screen1->addSeat(new Seat("A2", SeatType::SILVER));
    screen1->addSeat(new Seat("B1", SeatType::GOLD));
    screen1->addSeat(new Seat("B2", SeatType::GOLD));
    screen1->addSeat(new Seat("C1", SeatType::PLATINUM));
    cinema->addScreen(screen1);

    Screen* screen2 = new Screen(2);
    screen2->addSeat(new Seat("A1", SeatType::SILVER));
    screen2->addSeat(new Seat("A2", SeatType::SILVER));
    screen2->addSeat(new Seat("B1", SeatType::GOLD));
    cinema->addScreen(screen2);

    BookingService* service = new BookingService(cinema);

    Movie* movie1 = new Movie("Kaithi 2", "Tamil", 148);
    Movie* movie2 = new Movie("Interstellar", "English", 169);
    moviesOut.push_back(movie1);
    moviesOut.push_back(movie2);

    service->addShow(new Show(1, movie1, screen1, "18:30"));
    service->addShow(new Show(2, movie1, screen2, "21:45"));
    service->addShow(new Show(3, movie2, screen1, "15:00"));

    return service;
}

void printSectionHeader(const string& text) {
    cout << "\n#####################################################\n";
    cout << "# " << text << "\n";
    cout << "#####################################################\n";
}

// Scripted demo: proves F1-F8 and all 4 required edge cases with no
// keyboard input, so it can be run non-interactively for submission.
void runScriptedDemo() {
    Cinema* cinema = nullptr;
    vector<Movie*> movies;
    BookingService* service = buildDemoCinema(cinema, movies);

    printSectionHeader("F1: List all movies currently playing");
    service->listMovies();

    printSectionHeader("F2: List shows for \"Kaithi 2\"");
    service->listShows("Kaithi 2");

    Show* show1 = service->findShowById(1);

    printSectionHeader("F3: Seat layout before any booking");
    service->showSeatLayout(show1);

    printSectionHeader("F4 + F5: Book seats A1, B1 (SILVER + GOLD) and price them");
    Customer* riya = new Customer("Riya Sharma", "9876500001");
    Booking* booking1 = service->bookSeats(show1, riya, {"A1", "B1"});
    cout << "Booking " << booking1->getBookingId() << " is PENDING. "
         << "Total = Rs. " << booking1->getTotalAmount()
         << " (expected 150 + 250 = 400)\n";

    printSectionHeader("Edge case 1: booking an already-BOOKED seat is rejected");
    Customer* amit = new Customer("Amit Verma", "9876500002");
    try {
        service->bookSeats(show1, amit, {"A1"});   // A1 is already booked above
    } catch (const std::exception& e) {
        cout << "Rejected as expected: " << e.what() << "\n";
    }

    printSectionHeader("Edge case 4: booking an invalid seat number is rejected");
    try {
        service->bookSeats(show1, riya, {"Z9"});
    } catch (const std::exception& e) {
        cout << "Rejected as expected: " << e.what() << "\n";
    }

    printSectionHeader("F6: Failed payment must NOT confirm the booking");
    UpiPayment badUpi("not-a-valid-upi-id");       // no '@' -> validation fails
    bool result1 = service->makePayment(booking1, badUpi);
    cout << "Payment succeeded? " << (result1 ? "yes" : "no")
         << " | Booking status is now " << (booking1->getStatus() == BookingStatus::CANCELLED ? "CANCELLED" : "other") << "\n";

    printSectionHeader("Edge case 2 verified: seats released after failed payment");
    service->showSeatLayout(show1);   // A1 and B1 should show AVAILABLE again

    printSectionHeader("F4+F5+F6+F7: Book again and pay successfully by UPI");
    Booking* booking2 = service->bookSeats(show1, riya, {"A1", "B1", "C1"});
    UpiPayment goodUpi("riya@okhdfcbank");
    bool result2 = service->makePayment(booking2, goodUpi);   // prints ticket (F7) on success
    cout << "Payment succeeded? " << (result2 ? "yes" : "no") << "\n";

    printSectionHeader("F8: Cancel booking " + std::to_string(booking2->getBookingId()));
    service->cancelBooking(booking2);

    printSectionHeader("Edge case 3 verified: cancelled booking's seats are AVAILABLE again");
    service->showSeatLayout(show1);

    delete riya;
    delete amit;
    for (Movie* m : movies) delete m;
    delete service;   // cascades: deletes shows and bookings
    delete cinema;    // cascades: deletes screens, which delete their seats
}

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") {
        runScriptedDemo();
        return 0;
    }

    Cinema* cinema = nullptr;
    vector<Movie*> movies;
    BookingService* service = buildDemoCinema(cinema, movies);
    CinemaMenu menu(service);
    menu.run();
    delete service;
    delete cinema;
    for (Movie* m : movies) delete m;
    return 0;
}
