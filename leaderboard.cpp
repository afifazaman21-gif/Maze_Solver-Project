#include "Leaderboard.h"
#include <iostream>

using namespace std;

Leaderboard::Leaderboard(int cap) : count(0), capacity(cap) {
    players = new Player[cap];
}

Leaderboard::~Leaderboard() {
    delete[] players;
}

void Leaderboard::addPlayer(const Player& p) {
    if (count >= capacity) {
        cout << "Leaderboard full.\n";
        return;
    }
    players[count++] = p;
}

void Leaderboard::sortByScore() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j].getScore() < players[j + 1].getScore()) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

void Leaderboard::display() const {
    cout << "\n===== Leaderboard =====\n";
    if (count == 0) {
        cout << "No players yet.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". ";
        players[i].displayInfo();
    }
}