#include "Solver.h"

// Constructor: initializes MazeSolver with a pointer to the Maze
MazeSolver::MazeSolver(Maze* m) : mazePtr(m) {}
// Recursive Depth First Search (DFS) to find path from Start to End
bool MazeSolver::dfs(int r, int c) {
     // Check if current position is out of maze bounds
    if (r < 0 || r >= mazePtr->getRows() || c < 0 || c >= mazePtr->getCols())
        return false;
 // Get value of current cell
    char cell = mazePtr->getCell(r, c);
 // If cell is a wall or already visited, stop exploration
    if (cell == '#' || cell == '.') return false;
     // If destination 'E' is reached, return success
    if (cell == 'E') return true;
 // Mark current cell as visited (except start)
    if (cell != 'S')
        mazePtr->setCell(r, c, '.');

        // Explore all four directions: down, up, right, left
    if (dfs(r + 1, c) || dfs(r - 1, c) || dfs(r, c + 1) || dfs(r, c - 1)) {
        if (cell != 'S' && cell != 'E')
            mazePtr->setCell(r, c, '*');
        return true;
    }
 // Backtrack: reset cell if it does not lead to solution
    if (cell != 'S')
        mazePtr->setCell(r, c, ' ');

    return false;
}
// Solve function: finds starting point 'S' and initiates DFS
bool MazeSolver::solve() {
     // Check if maze pointer is valid
    if (!mazePtr) throw MazeLogicException("No maze assigned to solver.");

     // Traverse maze to locate start position 'S'
    for (int i = 0; i < mazePtr->getRows(); i++)
        for (int j = 0; j < mazePtr->getCols(); j++)
            if (mazePtr->getCell(i, j) == 'S')
                return dfs(i, j); // Start DFS from 'S'

    throw MazeLogicException("Start point 'S' not found.");
}