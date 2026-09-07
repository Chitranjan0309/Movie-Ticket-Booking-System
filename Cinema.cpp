// Cinema.cpp
// Single responsibility: the theatre itself - a name and its screens.
// Knows: its screens.
// Does: lets the service layer look screens up.
// Must NOT do: run the booking flow itself (that is BookingService's job).
#ifndef CINEMA_CINEMA_INCLUDED
#define CINEMA_CINEMA_INCLUDED

#include <string>
#include <vector>
#include "Screen.cpp"
using std::string;
using std::vector;

class Cinema {
private:
    string name;
    vector<Screen*> screens;   // Composition: screens belong to this cinema

public:
    explicit Cinema(const string& name) : name(name) {}

    ~Cinema() {
        for (Screen* s : screens) delete s;
    }

    void addScreen(Screen* screen) { screens.push_back(screen); }
    const vector<Screen*>& getScreens() const { return screens; }
    string getName() const { return name; }
};

#endif
