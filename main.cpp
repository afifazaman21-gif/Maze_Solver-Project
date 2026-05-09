#include <iostream>
#include "Maze.h" //Maze generation + display
#include "UserPlayer.h"  //User and Player classes
#include "Solver.h" //DFS maze solving
#include "Leaderboard.h" //Ranking players
#include "ManualPlay.h" W/A/S/D gameplay

using namespace std;

int main() {
    cout << "=============================================\n";
    cout << "       MAZE SOLVER - CS112 Project          \n";
    cout << "=============================================\n";

    Maze currentMaze(21, 21); //maze class object, maze size 21 rows, 21 column
    currentMaze.generateMaze();  //This line creates: paths, start point, end point

    Leaderboard board(50); //capable of storing maximum 50 players

    int choice; //Stores menu option user enters
    bool running = true;

    while (running) { //This repeatedly shows menu until user exits.
        cout << "\n======= MAIN MENU =======\n";
        cout << "1. Register Player\n";
        cout << "2. Player Login\n";
        cout << "3. Leaderboard\n";
        cout << "4. Generate New Maze\n";
        cout << "5. Exit\n";
        cout << "=========================\n";
        cout << "Choice: ";
        cin >> choice;

        try { //Any exception/error thrown inside:
            if (choice == 1) { //Register Player
                string uname, pass;
                cout << "Choose Username: ";
                cin >> uname;

                cout << "Choose Password: ";
                cin >> pass;

                Player newPlayer(uname, pass);
                newPlayer.saveToFile();
                cout << "Registered successfully! You can now login.\n";
                board.addPlayer(newPlayer); //Adds player into leaderboard array.
            }

            else if (choice == 2) { //Runs when user selects login.
                string uname, pass;
                cout << "Username: ";
                cin >> uname;

                cout << "Password: ";
                cin >> pass;
                Player p;
                p.loadFromFile(uname);

                if (!p.checkPassword(pass)) //if password is incorrect
                    throw LoginException("Incorrect password.");
                //Program jumps directly to catch (exception handling)
                p.login(); //isLoggedIn = true inside Player class.
                cout << "\nWelcome, " << p.getUsername() << "!\n"; //Uses getter function

                int pc; //Stores player menu choice
                bool prun = true; //Controls player menu loop

                 while (prun) { //keep showing player menu until player logs out
                    //Without this player menu appears once

                    //using polymorphism 
                    User* pu = &p; //is a pointer of base class type.
                    //base class pointer → derived class object, this is allowed bcz Player inherits User
                    showUserMenu(pu);
                    //Inside function:
                    //u->showMenu();
                    //Since showMenu() is virtual, C++ calls: Player's showMenu(), NOT User's.
                    //Runtime Polymorphism

                    cin >> pc;  //Stores submenu option

                    if (pc == 1) { //Runs when player chooses 1. View Maze
                        currentMaze.display();
                    }
                    else if (pc == 2) { //Runs gameplay mode
                        playManual(currentMaze, p); //Function receives maze object, player object
                        //player moves using W/A/S/D
                        //steps counted
                        //score updated
                        //maze displayed repeatedly
                    }
                    else if (pc == 3) { //This is your DFS feature, auto solve
                        currentMaze.clearVisitedAndPath();

                        Maze solveMaze = currentMaze; //Creates duplicate maze, because DFS changes maze cells
                        // If you directly solve currentMaze, your original maze gets modified permanently, So we solve a COPY instead
                        MazeSolver solver(&solveMaze);
                        //Passes maze address into solver, Now solver can access maze functions
                        if (solver.solve()) {
                            cout << "\nSolved using DFS! Path marked '*':\n";
                            solveMaze.display();
                            p.addScore(50);
                            cout << "You earned 50 points for auto-solve!\n";
                        }
                        else {
                            cout << "No solution found.\n";
                        }

                    //If file saving fails, game should continue, not crash
                        try { p.saveToFile(); } catch (...) {} //Attempts to save score
                    }
                    else if (pc == 4) {
                        p.displayInfo();
                    }
                    else if (pc == 5) {
                        p.logout(); //inside Player class
                        board.addPlayer(p); //Stores updated player data into leaderboard
                        prun = false; //Player returns to main menu
                    }
                }
            }

            else if (choice == 3) {
                board.sortByScore();
                board.display(); //Prints rankings
            }

            else if (choice == 4) {
                currentMaze.generateMaze(); //Creates brand new random maze
                cout << "\nNew maze generated!\n";
                currentMaze.display();
            }

            else if (choice == 5) {
                running = false;
                cout << "Goodbye!\n";
            }

            else {
                cout << "Invalid choice.\n";
            }
        //handles errors safely.
        } catch (LoginException& e) { //catches Incorrect password
            cout << "\n[!] " << e.what() << "\n";
        } catch (FileException& e) { //Handles missing files, save/load failures
            cout << "\n[!] " << e.what() << "\n";
        } catch (MazeLogicException& e) { //Handles maze-related issues
            //Example No start point found
            cout << "\n[!] " << e.what() << "\n";
        } catch (MazeException& e) { //Handles standard library errors
            cout << "\n[!] " << e.what() << "\n";
        } catch (exception& e) {
            cout << "\n[!] Standard exception: " << e.what() << "\n";
        } catch (...) { //Catches ANYTHING missed earlier
            cout << "\n[!] Unknown error occurred.\n";
        }
    }

    return 0;
}