// Common.cpp
// Shared enums and constants used by every class in the system.
// Kept in one place so a price change (F5) never forces edits inside
// unrelated classes -> supports the Open/Closed Principle (see report, Step H).
#ifndef CINEMA_COMMON_INCLUDED
#define CINEMA_COMMON_INCLUDED

#include <string>

// ---- constants instead of magic numbers (clean-code checklist) ----
const double SILVER_PRICE   = 150.0;
const double GOLD_PRICE     = 250.0;
const double PLATINUM_PRICE = 400.0;

enum class SeatType { SILVER, GOLD, PLATINUM };

enum class SeatStatus { AVAILABLE, BOOKED };

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED };

// small free helper used by Seat::getPrice() and PriceCalculator
inline double priceForSeatType(SeatType type) {
    switch (type) {
        case SeatType::SILVER:   return SILVER_PRICE;
        case SeatType::GOLD:     return GOLD_PRICE;
        case SeatType::PLATINUM: return PLATINUM_PRICE;
    }
    return 0.0; // unreachable, keeps compiler happy
}

inline std::string seatTypeToString(SeatType type) {
    switch (type) {
        case SeatType::SILVER:   return "SILVER";
        case SeatType::GOLD:     return "GOLD";
        case SeatType::PLATINUM: return "PLATINUM";
    }
    return "UNKNOWN";
}

#endif
