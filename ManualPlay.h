#ifndef MANUALPLAY_H
#define MANUALPLAY_H
// Header guard → prevents this file from being included multiple times

#include "Maze.h"
// Includes Maze class definition

#include "UserPlayer.h"
// Includes Player class definition

void playManual(Maze& maze, Player& player);
// Function declaration for manual gameplay
// Maze& maze → passes maze object by reference
// Player& player → passes player object by reference
// '&' means original objects are used, not copies

#endif
// End of header guard