#include "ManualPlay.h"
// Includes function declaration and required classes

#include <iostream>
// Used for input and output (cout, cin)

#include <cctype>
// Used for character functions like tolower()

using namespace std;
// Allows use of cout/cin without std::

void playManual(Maze& maze, Player& player) {
    // Function for manually playing the maze game
    // Maze and Player are passed by reference

    cout << "\n[Manual Mode] Navigate with W/A/S/D. Reach 'E' to win!\n";
    // Displays game instructions

    maze.display();
    // Shows the maze on screen

    int pr = -1, pc = -1;
    // pr = player row position
    // pc = player column position
    // Initialized with -1 meaning "not found yet"

    for (int i = 0; i < maze.getRows() && pr == -1; i++)
        // Loop through maze rows until start position is found

        for (int j = 0; j < maze.getCols() && pr == -1; j++)
            // Loop through maze columns

            if (maze.getCell(i, j) == 'S') {
                // Checks if current cell contains starting point 'S'

                pr = i;
                // Save row position

                pc = j;
                // Save column position
            }

    if (pr == -1) {
        // If start position was not found

        cout << "No start 'S' found!\n";
        // Error message

        return;
        // Exit function
    }

    player.incrementAttempt();
    // Increases player's attempt count

    int steps = 0;
    // Counts how many moves player makes

    while (true) {
        // Infinite loop until player wins or quits

        cout << "\nMove (W=Up  A=Left  S=Down  D=Right  Q=Quit): ";
        // Ask user for movement input

        char move;
        cin >> move;
        // Take movement input

        move = tolower(move);
        // Converts uppercase input into lowercase

        int nr = pr, nc = pc;
        // nr = new row
        // nc = new column
        // Initially same as current position

        if (move == 'w') nr--;
        // Move up

        else if (move == 's') nr++;
        // Move down

        else if (move == 'a') nc--;
        // Move left

        else if (move == 'd') nc++;
        // Move right

        else if (move == 'q') {
            // If player wants to quit

            cout << "Quit manual mode.\n";

            return;
            // Exit game
        }

        else {
            // Invalid key entered

            cout << "Invalid key!\n";

            continue;
            // Restart loop
        }

        if (nr < 0 || nr >= maze.getRows() || nc < 0 || nc >= maze.getCols()) {
            // Checks if player goes outside maze boundaries

            cout << "Out of bounds!\n";

            continue;
            // Ignore move and continue
        }

        char dest = maze.getCell(nr, nc);
        // Gets character at destination cell

        if (dest == '#') {
            // '#' represents a wall

            cout << "That's a wall!\n";

            continue;
            // Cannot move into wall
        }

        if (maze.getCell(pr, pc) != 'S')
            // Checks if previous position is not starting point

            maze.setCell(pr, pc, '.');
            // Marks previous position as visited

        pr = nr;
        // Update current row position

        pc = nc;
        // Update current column position

        steps++;
        // Increase step counter

        maze.display();
        // Display updated maze

        if (dest == 'E') {
            // If destination is exit point 'E'

            cout << "\n*** You reached the exit in " << steps << " steps! ***\n";
            // Winning message

            int pts = max(1, 100 - steps);
            // Calculate points
            // More steps = fewer points
            // Minimum score = 1

            player.addScore(pts);
            // Add earned points to player score

            cout << "Points earned: " << pts
                 << " | Total Score: "
                 << player.getScore() << "\n";
            // Display earned points and total score

            try {
                player.saveToFile();
            }
            // Save player data into file

            catch (...) {}
            // Ignore any file saving errors

            return;
            // Exit game after winning
        }
    }
}