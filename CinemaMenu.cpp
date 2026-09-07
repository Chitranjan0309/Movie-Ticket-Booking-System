// CinemaMenu.cpp
// Single responsibility: the console menu - reads input, shows menus, and
// delegates every real decision to BookingService. No business rule lives
// here (that separation is what lets BookingService be reused, e.g. behind
// a web API, without rewriting this class).
// Knows: which BookingService to talk to.
// Does: prints menus, reads input, calls BookingService.
// Must NOT do: touch Show/ShowSeat/Booking internals directly.
#ifndef CINEMA_MENU_INCLUDED
#define CINEMA_MENU_INCLUDED

#include <iostream>
#include <sstream>
#include <limits>
#include "BookingService.cpp"
#include "Customer.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
using std::cout;
using std::cin;
using std::endl;
using std::string;

class CinemaMenu {
private:
    BookingService* service;

    static vector<string> splitBySpace(const string& line) {
        vector<string> tokens;
        std::istringstream stream(line);
        string token;
        while (stream >> token) tokens.push_back(token);
        return tokens;
    }

    int readIntChoice() {
        int choice;
        while (!(cin >> choice)) {                 // edge case 4: invalid menu input
            cout << "That is not a valid number. Try again: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return choice;
    }

public:
    explicit CinemaMenu(BookingService* service) : service(service) {}

    void run() {
        bool exit = false;
        while (!exit) {
            cout << "\n===== MOVIE TICKET BOOKING =====\n";
            cout << "1. List movies\n";
            cout << "2. List shows for a movie\n";
            cout << "3. View seat layout for a show\n";
            cout << "4. Book seats\n";
            cout << "5. Cancel a booking\n";
            cout << "6. Exit\n";
            cout << "Choose an option: ";

            int choice = readIntChoice();
            switch (choice) {
                case 1: service->listMovies(); break;
                case 2: handleListShows(); break;
                case 3: handleSeatLayout(); break;
                case 4: handleBooking(); break;
                case 5: handleCancel(); break;
                case 6: exit = true; break;
                default: cout << "Invalid option. Please choose 1-6.\n";   // edge case 4
            }
        }
        cout << "Thank you for using the booking system.\n";
    }

private:
    void handleListShows() {
        cout << "Enter movie title: ";
        cin.ignore();
        string title;
        std::getline(cin, title);
        service->listShows(title);
    }

    Show* promptForShow() {
        cout << "Enter show id: ";
        int showId = readIntChoice();
        Show* show = service->findShowById(showId);
        if (show == nullptr) {
            cout << "No such show id.\n";           // edge case 4
        }
        return show;
    }

    void handleSeatLayout() {
        Show* show = promptForShow();
        if (show != nullptr) service->showSeatLayout(show);
    }

    void handleBooking() {
        Show* show = promptForShow();
        if (show == nullptr) return;

        service->showSeatLayout(show);
        cout << "Enter seat numbers to book (space separated, e.g. A1 A2): ";
        cin.ignore();
        string line;
        std::getline(cin, line);
        vector<string> seatNumbers = splitBySpace(line);

        cout << "Customer name: ";
        string name;
        std::getline(cin, name);
        cout << "Customer phone: ";
        string phone;
        std::getline(cin, phone);
        Customer* customer = new Customer(name, phone);

        Booking* booking = nullptr;
        try {
            booking = service->bookSeats(show, customer, seatNumbers);   // F4, F5
        } catch (const std::exception& e) {
            cout << "Booking failed: " << e.what() << "\n";              // edge cases 1, 4
            return;
        }

        cout << "Seats reserved. Total amount: Rs. " << booking->getTotalAmount() << "\n";
        cout << "Pay by (1) UPI  (2) Card  (3) Cash: ";
        int payChoice = readIntChoice();

        Payment* payment = nullptr;
        if (payChoice == 1) {
            cout << "Enter UPI id: ";
            string upiId; cin.ignore(); std::getline(cin, upiId);
            payment = new UpiPayment(upiId);
        } else if (payChoice == 2) {
            cout << "Enter 16-digit card number: ";
            string cardNumber; cin.ignore(); std::getline(cin, cardNumber);
            payment = new CardPayment(cardNumber);
        } else {
            payment = new CashPayment();
        }

        service->makePayment(booking, *payment);   // F6 -> prints ticket (F7) on success
        delete payment;
    }

    void handleCancel() {
        cout << "Enter booking id to cancel: ";
        int bookingId = readIntChoice();
        Booking* booking = service->findBookingById(bookingId);
        if (booking == nullptr) {
            cout << "No such booking id.\n";        // edge case 4
            return;
        }
        service->cancelBooking(booking);            // F8
    }
};

#endif
