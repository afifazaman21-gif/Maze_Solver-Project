#include "UserPlayer.h"
#include <iostream>
#include <fstream>

using namespace std;

// USER CLASS IMPLEMENTATION
// Default constructor → empty user
User::User() : username(""), password(""), score(0) {}

// Constructor with username + password
User::User(const string& uname, const string& pass)
    : username(uname), password(pass), score(0) {}

// Display basic info
void User::displayInfo() const {
    cout << "Username: " << username << " | Score: " << score << "\n";
}

// Getter functions
string User::getUsername() const { return username; }
int User::getScore() const { return score; }

// Add points to score
void User::addScore(int pts) { score += pts; }

// Check password match
bool User::checkPassword(const string& pass) const {
    return password == pass;
}

// Destructor (nothing dynamic → empty)
User::~User() {}



// PLAYER CLASS IMPLEMENTATION

// Default Player
Player::Player() : User(), attemptCount(0), isLoggedIn(false) {}

// Player with credentials
Player::Player(const string& uname, const string& pass)
    : User(uname, pass), attemptCount(0), isLoggedIn(false) {}


// Login/logout controls
void Player::login() { isLoggedIn = true; }
void Player::logout() { isLoggedIn = false; }

// Increase maze attempt counter
void Player::incrementAttempt() { attemptCount++; }


// Player Menu (Runtime Polymorphism)
void Player::showMenu() {
    cout << "\n--- Player Menu [" << username << "] ---\n";
    cout << "1. View Maze\n";
    cout << "2. Manual Play\n";
    cout << "3. Auto-Solve (DFS)\n";
    cout << "4. My Stats\n";
    cout << "5. Logout\n";
    cout << "Choice: ";
}


// Overridden display function (Function Overriding)
void Player::displayInfo() const {
    cout << "[Player] " << username
         << " | Score: " << score
         << " | Attempts: " << attemptCount << "\n";
}


// FILE HANDLING FUNCTIONS
// Save player data to file
void Player::saveToFile() const {
    string fname = username + "_data.txt";   // filename creation
    ofstream fout(fname);                    // open file for writing

    if (!fout.is_open())
        throw FileException("Could not save player data.");

    // Write data line-by-line
    fout << username << "\n"
         << password << "\n"
         << score << "\n"
         << attemptCount << "\n";

    fout.close();
}


// Load player data from file
void Player::loadFromFile(const string& uname) {
    string fname = uname + "_data.txt";
    ifstream fin(fname);

    if (!fin.is_open())
        throw FileException("No saved data for: " + uname);

    // Read in same order as saved
    getline(fin, username);
    getline(fin, password);
    fin >> score >> attemptCount;

    fin.close();
}
// POLYMORPHISM FUNCTION
// Calls virtual function via base pointer

void showUserMenu(User* u) {
    u->showMenu();
}

// FRIEND FUNCTION IMPLEMENTATION 

// Not a member of Player class!
// But declared as friend → can access private members
void grantSecretBonus(Player& p) {

    // Direct access to PROTECTED member 'score'
    p.score += 10;

    cout << "\n[Friend Function] Secret bonus granted to "
         << p.username << " (+10 points)\n";
}