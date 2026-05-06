#include "Maze.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Default constructor: initializes rows/cols
Maze::Maze()
    : rows(0), cols(0), grid(nullptr),
      rng((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}

// Parameterized constructor: sets dimensions, allocates memory, and fills with walls
Maze::Maze(int r, int c)
    : rows(r), cols(c),
      rng((unsigned)chrono::steady_clock::now().time_since_epoch().count())
{
    allocateGrid();
    fillWalls();
}

// Helper to handle dynamic 2D array allocation
void Maze::allocateGrid() {
    grid = new CellType*[rows];
    for (int i = 0; i < rows; i++)
        grid[i] = new CellType[cols];
}

// Sets every cell in the grid to a WALL type
void Maze::fillWalls() {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = CellType::WALL;
}

// Checks if a given coordinate is within the array bounds
bool Maze::isInBounds(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

// Recursive backtracking algorithm to "dig" the maze paths
void Maze::carve(int r, int c) {
    grid[r][c] = CellType::EMPTY;

// Directions: Up, Down, Left, Right (jumping 2 cells to maintain walls)
int dirs[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };

// Shuffle to randomize direction order
for (int i = 3; i > 0; --i) {
     uniform_int_distribution<int> dist(0, i);
    int j = dist(rng);
    swap(dirs[i][0], dirs[j][0]);
    swap(dirs[i][1], dirs[j][1]);
}

for (auto& d : dirs) {
    int nr = r + d[0];
    int nc = c + d[1];

// If the target cell is a wall, carve a path through the wall in between
if (isInBounds(nr, nc) && grid[nr][nc] == CellType::WALL) {
     grid[r + d[0] / 2][c + d[1] / 2] = CellType::EMPTY;
    carve(nr, nc);
    }
}
}

// Copy Constructor: creates a deep copy of another Maze object
Maze::Maze(const Maze& other)
    : rows(other.rows), cols(other.cols),
      rng((unsigned)chrono::steady_clock::now().time_since_epoch().count())
{
    allocateGrid();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = other.grid[i][j];
}

// Destructor: cleans up dynamically allocated memory to prevent leaks
Maze::~Maze() {
    if (grid != nullptr) {
        for (int i = 0; i < rows; i++)
            delete[] grid[i];
        delete[] grid;
        grid = nullptr;
    }
}

// Assignment Operator: handles deep copying and cleans up existing memory
Maze& Maze::operator=(const Maze& other) {
    if (this == &other) return *this;

    if (grid) {
        for (int i = 0; i < rows; i++)
            delete[] grid[i];
        delete[] grid;
    }
    rows = other.rows;
    cols = other.cols;
    allocateGrid();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = other.grid[i][j];

    return *this;
}