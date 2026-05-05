#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <string>
#include "Exceptions.h"   // bring in custom error handling

using namespace std;

// Base class for all users in the system
class User {
protected:
    string username;   
    string password;   
    int score;         

public:
    User();   
    User(const string& uname, const string& pass);   // create user with name + password

    virtual void showMenu() = 0;   // force subclasses to show their own menu
    virtual void displayInfo() const;   // show basic user details

    string getUsername() const;   // fetch the username
    int getScore() const;         // fetch the score
    void addScore(int pts);       // add points to score

    bool checkPassword(const string& pass) const;   // verify password

    virtual ~User();   // cleanup when object is destroyed
};

// Player class extends User with extra features
class Player : public User {
private:
    int attemptCount;   // how many times player tried to log in
    bool isLoggedIn;    // track login status

public:
    Player();   // default player
    Player(const string& uname, const string& pass);   // player with name + password

    void login();             
    void logout();            
    void incrementAttempt();  // increase failed login attempts

    void showMenu() override;        // show player-specific menu
    void displayInfo() const override;   // show player details

    void saveToFile() const;            // save player data to file
    void loadFromFile(const string& uname);   // load player data from file
};

// helper function to show menu for any user type
void showUserMenu(User* u);

#endif
