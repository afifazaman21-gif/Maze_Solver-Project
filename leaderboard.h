#ifndef LEADERBOARD_H
#define LEADERBOARD_H
// Header guard start → prevents this file from being included multiple times

#include "UserPlayer.h"
// Includes the file where Player class is defined

class Leaderboard {
    // Declaring a class named Leaderboard

private:
    Player* players;
    // Pointer to dynamically store an array of Player objects

    int count;
    // Keeps track of how many players are currently added

    int capacity;
    // Maximum number of players the leaderboard can hold

public:
    Leaderboard(int cap = 10);
    // Constructor → initializes leaderboard
    // Default capacity is 10 if no value is given

    ~Leaderboard();
    // Destructor → used to free allocated memory (like deleting players array)

    void addPlayer(const Player& p);
    // Function to add a new player
    // 'const Player&' → passed by reference and cannot be modified

    void sortByScore();
    // Function to sort players based on their scores

    void display() const;
    // Function to display leaderboard
    // 'const' → this function does not modify any data
};

#endif
// End of header guard