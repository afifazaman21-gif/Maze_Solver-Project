#include "ManualPlay.h"
#include <iostream>
#include <cctype>

using namespace std;

void playManual(Maze& maze, Player& player) {
    cout << "\n[Manual Mode] Navigate with W/A/S/D. Reach 'E' to win!\n";
    maze.display();

    int pr = -1, pc = -1;
    for (int i = 0; i < maze.getRows() && pr == -1; i++)
        for (int j = 0; j < maze.getCols() && pr == -1; j++)
            if (maze.getCell(i, j) == 'S') {
                pr = i;
                pc = j;
            }

    if (pr == -1) {
        cout << "No start 'S' found!\n";
        return;
    }

    player.incrementAttempt();
    int steps = 0;

    while (true) {
        cout << "\nMove (W=Up  A=Left  S=Down  D=Right  Q=Quit): ";
        char move;
        cin >> move;

        move = tolower(move);

        int nr = pr, nc = pc;
        if (move == 'w') nr--;
        else if (move == 's') nr++;
        else if (move == 'a') nc--;
        else if (move == 'd') nc++;
        else if (move == 'q') {
            cout << "Quit manual mode.\n";
            return;
        }
        else {
            cout << "Invalid key!\n";
            continue;
        }

        if (nr < 0 || nr >= maze.getRows() || nc < 0 || nc >= maze.getCols()) {
            cout << "Out of bounds!\n";
            continue;
        }

        char dest = maze.getCell(nr, nc);

        if (dest == '#') {
            cout << "That's a wall!\n";
            continue;
        }

        if (maze.getCell(pr, pc) != 'S')
            maze.setCell(pr, pc, '.');

        pr = nr;
        pc = nc;
        steps++;

        maze.display();

        if (dest == 'E') {
            cout << "\n*** You reached the exit in " << steps << " steps! ***\n";
            int pts = max(1, 100 - steps);
            player.addScore(pts);
            cout << "Points earned: " << pts << " | Total Score: " << player.getScore() << "\n";
            try { player.saveToFile(); } catch (...) {}
            return;
        }
    }
}