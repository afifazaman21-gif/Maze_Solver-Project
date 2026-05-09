#include "UserPlayer.h"
#include <iostream>
#include <fstream>

using namespace std;

// ---------------- USER CLASS ----------------

// Default constructor: initializes empty user
User::User() : username(""), password(""), score(0) {}

// Parameterized constructor: sets username and password
User::User(const string& uname, const string& pass)
    : username(uname), password(pass), score(0) {}

// Prints basic user info (username + score)
void User::displayInfo() const {
    cout << "Username: " << username << " | Score: " << score << "\n";
}

// Getters for user data
string User::getUsername() const { return username; }
int User::getScore() const { return score; }

// Adds points to user score
void User::addScore(int pts) { score += pts; }

// Simple password check
bool User::checkPassword(const string& pass) const { return password == pass; }

// Destructor (nothing dynamic here, so empty)
User::~User() {}


// ---------------- PLAYER CLASS ----------------

// Default player setup
Player::Player() : User(), attemptCount(0), isLoggedIn(false) {}

// Player with credentials
Player::Player(const string& uname, const string& pass)
    : User(uname, pass), attemptCount(0), isLoggedIn(false) {}

// Marks player as logged in
void Player::login() { isLoggedIn = true; }

// Marks player as logged out
void Player::logout() { isLoggedIn = false; }

// Tracks how many attempts player made in maze
void Player::incrementAttempt() { attemptCount++; }

// Displays player menu options
void Player::showMenu() {
    cout << "\n--- Player Menu [" << username << "] ---\n";
    cout << "1. View Maze\n";
    cout << "2. Manual Play\n";
    cout << "3. Auto-Solve (DFS)\n";
    cout << "4. My Stats\n";
    cout << "5. Logout\n";
    cout << "Choice: ";
}

// Overridden info display with extra stats
void Player::displayInfo() const {
    cout << "[Player] " << username
         << " | Score: " << score
         << " | Attempts: " << attemptCount << "\n";
}

// Saves player data to a file (username_data.txt)
void Player::saveToFile() const {
    string fname = username + "_data.txt";
    ofstream fout(fname);

    // If file can't be created, throw error
    if (!fout.is_open()) throw FileException("Could not save player data.");

    // Store user details line by line
    fout << username << "\n" << password << "\n" << score << "\n" << attemptCount << "\n";
    fout.close();
}

// Loads player data from file
void Player::loadFromFile(const string& uname) {
    string fname = uname + "_data.txt";
    ifstream fin(fname);

    // If file doesn't exist, throw error
    if (!fin.is_open()) throw FileException("No saved data for: " + uname);

    // Read data back in same order it was saved
    getline(fin, username);
    getline(fin, password);
    fin >> score >> attemptCount;

    fin.close();
}

// Helper function: calls menu from user pointer (polymorphism use)
void showUserMenu(User* u) {
    u->showMenu();
}