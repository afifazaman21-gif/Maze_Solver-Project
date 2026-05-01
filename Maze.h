#ifndef MAZE_H // Header Guard:
#define MAZE_H // Prevents this file from multiple inclusions in the same program
// which causes "redefinition" compilation errors

#include <random>  // Provides random number generation tools such as mt19937 and distributions
//for generating random maze paths

#include <chrono>  // Provides time-related functions
// for generating a unique seed (current time) for random number generator.

#include "Exceptions.h" // Includes custom exception classes (FileException, MazeLogicException, etc.)
// Used to handle errors like invalid maze size or out-of-bounds access.

//creating enum CellType
// represents the type of each cell is in the maze.  
// using enum class for strong type safety
enum class CellType{
    WALL,            // Wall cell (not walkable)
    EMPTY,           // Empty cell (walkable path)
    START,           // Start position 'S'
    END,             // End position 'E'
    VISITED,         // Visited cell '.' during solving/manual play
    PATH             // Final solution path '*'
};
// This class handles:
// 1. Dynamic 2D maze grid creation (using pointers)
// 2. Random maze generation (carving algorithm)
// 3. Displaying maze using clear ASCII symbols
// 4. Updating maze during manual play and solving
class Maze {
private:
    // Maze dimensions
    int rows, cols;

    CellType** grid; // Dynamic 2D grid storing CellType values
    // grid[i][j] represents the cell at row i and column j

    std::mt19937 rng; // Random number generator (used for random maze generation)

    //helper functions
    void allocateGrid();
    // Dynamic memory allocation for the 2D maze grid
    // Uses new[] to create rows and columns in heap memory

    void fillWalls(); 
    // Sets all cells in the maze as walls initially
    // Maze carving algorithm will later create paths

    bool isInBounds(int r, int c) const; 
    // Checks if a given (row, col) is inside the maze boundary
    // Returns true if valid, false otherwise

    void carve(int r, int c); 
    // Recursive maze carving algorithm
    // It breaks walls randomly to create a solvable maze
    // Uses DFS-like recursion with random direction shuffling

public:
    Maze(); // Default Constructor
    // Creates an empty maze object with no grid

    Maze(int r, int c);  // Parameterized Constructor
    // Creates a maze of given size (rows x cols) and initializes grid

    
    Maze(const Maze& other);// Copy Constructor
    // Performs deep copy of the maze grid
    // Prevents shallow copy issues (double delete problem)

    ~Maze();   // Destructor
    // Frees dynamically allocated memory of the maze grid
    // Prevents memory leaks

    Maze& operator=(const Maze& other); // Assignment Operator Overloading (=)
    // Allows safe deep-copy assignment between Maze objects
    // Example: maze1 = maze2;

    int getRows() const; // Getter functions for maze size
    int getCols() const;

    char getCell(int r, int c) const; 
    // Returns the character representation of a cell
    // Example: '#' for wall, 'S' for start, etc
    // Used for display and solver logic
   
    void setCell(int r, int c, char val);
    // Updates a maze cell by converting given character into CellType
    // Throws exception if index is out of bounds

    void generateMaze();
    // Generates a random maze using carving algorithm.
    // Also sets Start at (1,1) and End at (rows-2, cols-2)

    void clearVisitedAndPath();
    // Clears only visited cells '.' and solution path '*'
    // so the maze can be solved again after manual play

    void display() const;
    // Prints the maze on console using clear symbols
    // Walls are displayed as █ blocks for better visuals
};
#endif