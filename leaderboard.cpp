#include "Leaderboard.h"
// Includes the header file where Leaderboard class is declared

#include <iostream>
// Includes input-output library (for cout)

using namespace std;
// So we can use cout without writing std::cout

Leaderboard::Leaderboard(int cap) : count(0), capacity(cap) {
    // Constructor definition
    // Initializes count to 0 (no players yet)
    // Initializes capacity with given value (cap)

    players = new Player[cap];
    // Dynamically allocates an array of Player objects of size 'cap'
}

Leaderboard::~Leaderboard() {
    // Destructor definition (called automatically when object is destroyed)

    delete[] players;
    // Frees the dynamically allocated memory to avoid memory leak
}

void Leaderboard::addPlayer(const Player& p) {
    // Function to add a new player into leaderboard
    // 'const Player& p' → passed by reference and cannot be modified

    if (count >= capacity) {
        // Checks if leaderboard is already full

        cout << "Leaderboard full.\n";
        // Prints message if no more space

        return;
        // Exits function without adding player
    }

    players[count++] = p;
    // Adds player at index 'count'
    // Then increments count by 1 (post-increment)
}void Leaderboard::sortByScore() {
    // Function to sort players based on score (highest first)

    for (int i = 0; i < count - 1; i++) {
        // Outer loop → runs multiple passes

        for (int j = 0; j < count - i - 1; j++) {
            // Inner loop → compares adjacent players

            if (players[j].getScore() < players[j + 1].getScore()) {
                // If current player's score is LESS than next player's score
                // → we swap them to bring higher score forward

                Player temp = players[j];
                // Store current player in temporary variable

                players[j] = players[j + 1];
                // Move next player to current position

                players[j + 1] = temp;
                // Put stored player in next position (swap complete)
            }
        }
    }
    // This is Bubble Sort (descending order → highest score first)
}

void Leaderboard::display() const {
    // Function to display all players
    // 'const' → does not modify any data

    cout << "\n===== Leaderboard =====\n";
    // Prints heading

    if (count == 0) {
        // Checks if no players exist

        cout << "No players yet.\n";
        // Prints message if empty

        return;
        // Exit function early
    }

    for (int i = 0; i < count; i++) {
        // Loop through all players

        cout << i + 1 << ". ";
        // Prints ranking number (1, 2, 3...)

        players[i].displayInfo();
        // Calls function to display player details (name, score, etc.)
    }
}