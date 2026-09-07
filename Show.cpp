// Show.cpp
// Single responsibility: one screening = a Movie on a Screen at a start time.
// Owns the ShowSeat objects created specifically for this screening.
// Knows: its movie, its screen, its own seat-booking state.
// Does: builds the per-show seat map once, prints the seat layout.
// Must NOT do: know about Customers, Bookings or Payments.
#ifndef CINEMA_SHOW_INCLUDED
#define CINEMA_SHOW_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Show {
private:
    int showId;
    Movie* movie;                 // aggregation: movie exists independently
    Screen* screen;                // aggregation: screen exists independently
    string startTime;             // e.g. "18:30"
    vector<ShowSeat*> showSeats;  // composition: created only for this show

public:
    Show(int showId, Movie* movie, Screen* screen, const string& startTime)
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {
        // one ShowSeat per physical seat on the assigned screen
        for (Seat* seat : screen->getSeats()) {
            showSeats.push_back(new ShowSeat(seat));
        }
    }

    ~Show() {
        for (ShowSeat* ss : showSeats) delete ss;
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    const vector<ShowSeat*>& getShowSeats() const { return showSeats; }

    // F3: display the seat layout with AVAILABLE / BOOKED status
    void printSeatLayout() const {
        cout << "\nSeat layout for \"" << movie->getTitle()
             << "\" | Screen " << screen->getScreenNumber()
             << " | " << startTime << "\n";
        for (ShowSeat* ss : showSeats) {
            cout << "  " << ss->getSeat()->getSeatNumber()
                 << " [" << seatTypeToString(ss->getSeat()->getType()) << "] : "
                 << (ss->isAvailable() ? "AVAILABLE" : "BOOKED") << "\n";
        }
    }
};

#endif
