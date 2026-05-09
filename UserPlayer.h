#ifndef USERPLAYER_H
#define USERPLAYER_H
#include <string>
#include "Exceptions.h"   // contains FileException etc

using namespace std;
// BASE CLASS : User (Abstract Class)
class User {
protected:
    // Protected so derived classes (Player) can access them
    string username;   
    string password;   
    int score;         

public:
    User();   
    User(const string& uname, const string& pass);

    // PURE VIRTUAL FUNCTION → makes class ABSTRACT
    // Every derived class MUST implement its own menu
    virtual void showMenu() = 0;

    // Virtual so Player can override it
    virtual void displayInfo() const;

    // Getters
    string getUsername() const;
    int getScore() const;

    // Add points to score
    void addScore(int pts);

    // Password verification
    bool checkPassword(const string& pass) const;

    // Virtual destructor (important in inheritance)
    virtual ~User();
};


// DERIVED CLASS : Player

class Player : public User {
private:
    int attemptCount;   // number of maze attempts
    bool isLoggedIn;    // login status

  
    // FRIEND CLASS 
    // Leaderboard can directly access private data
    // without using getters (exam concept)
    friend class Leaderboard;

    // FRIEND FUNCTION 
    // External function allowed to access private members
    friend void grantSecretBonus(Player& p);

public:
    Player();
    Player(const string& uname, const string& pass);

    void login();             
    void logout();            
    void incrementAttempt();  

    void showMenu() override;        
    void displayInfo() const override;

    // File handling
    void saveToFile() const;
    void loadFromFile(const string& uname);
};

// POLYMORPHISM HELPER FUNCTION
// Calls virtual menu using base pointer
void showUserMenu(User* u);

// FRIEND FUNCTION DECLARATION
// (must be declared outside class)
void grantSecretBonus(Player& p);

#endif