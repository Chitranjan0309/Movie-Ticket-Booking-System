// Movie.cpp
// Single responsibility: hold a movie's own data (title, language, duration).
// Knows: its own metadata.
// Does: exposes read-only getters.
// Must NOT do: know about shows, screens, or seats.
#ifndef CINEMA_MOVIE_INCLUDED
#define CINEMA_MOVIE_INCLUDED

#include <string>
using std::string;

class Movie {
private:                       // Encapsulation: no field is touched directly
    string title;
    string language;
    int durationMinutes;

public:
    Movie(const string& title, const string& language, int durationMinutes)
        : title(title), language(language), durationMinutes(durationMinutes) {}

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDurationMinutes() const { return durationMinutes; }
};

#endif
