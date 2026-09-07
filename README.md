📌 Project Overview

The Movie Ticket Booking System is a modular, console-based C++ application designed for managing movie shows, seat reservations, payments, ticket generation, and booking cancellation for a single cinema. The project follows Object-Oriented Programming (OOP), SOLID principles, clean coding practices, and modular system design.

🎯 Purpose

The main purpose of this project is to demonstrate how a real-world movie booking system can be designed using well-structured classes and relationships. It handles the complete booking flow—from selecting a movie and show to choosing seats, making payment, generating a ticket, and cancelling a booking.

✨ Features
🎥 List Movies — Displays currently playing movies with title, language, and duration.
🕐 Show Management — Displays available shows, screen numbers, and show timings.
💺 Seat Layout — Shows seat number, seat type, and availability.
🎟️ Seat Booking — Allows customers to book one or multiple available seats.
💰 Automatic Pricing
Silver — ₹150
Gold — ₹250
Platinum — ₹400
💳 Multiple Payment Methods — UPI, Card, and Cash.
🎫 Ticket Generation — Generates a ticket containing booking and payment details.
❌ Booking Cancellation — Cancels bookings using the booking ID and releases seats.
🛡️ Input Validation — Handles invalid menu choices, seat numbers, show IDs, and booking IDs without crashing.
🔄 Failed Payment Handling — Automatically releases reserved seats if payment fails.
🧩 SOLID Design — Implements all five SOLID principles.
🛠️ Technologies Used
Language: C++
Standard: C++17
Programming Paradigm: Object-Oriented Programming
Concepts: Encapsulation, Abstraction, Inheritance, Polymorphism
Design Principles: SOLID & Clean Code
UML: Class Diagram & Sequence Diagram
Build Tool: g++
Data Structures: STL vector and object-based relationships
Testing: AddressSanitizer (ASan) and UndefinedBehaviorSanitizer (UBSan)
Documentation: Markdown / UML / Graphviz diagrams
📂 Project Structure
Movie-Ticket-Booking-System/
│
├── code/
│   └── src/
│       ├── Common.cpp
│       ├── Movie.cpp
│       ├── Seat.cpp
│       ├── Screen.cpp
│       ├── Cinema.cpp
│       ├── ShowSeat.cpp
│       ├── Show.cpp
│       ├── Customer.cpp
│       ├── Payment.cpp
│       ├── UpiPayment.cpp
│       ├── CardPayment.cpp
│       ├── CashPayment.cpp
│       ├── Booking.cpp
│       ├── PriceCalculator.cpp
│       ├── TicketPrinter.cpp
│       ├── BookingService.cpp
│       ├── CinemaMenu.cpp
│       └── main.cpp
│
├── diagrams/
│   └── class_diagram.dot
│
└── README.md
