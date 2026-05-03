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
}