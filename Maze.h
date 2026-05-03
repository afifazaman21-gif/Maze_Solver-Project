#ifndef MAZE_H // Prevents this file from multiple inclusions 
#define MAZE_H 


#include <random>  // Provides random number generation tools
//for generating random maze paths

#include <chrono>  // Provides time-related functions

#include "Exceptions.h" // Includes custom exception classes

// represents the type of each cell is in the maze.  
enum class CellType{
    WALL,            
    EMPTY,           
    START,           
    END,            
    VISITED,         
    PATH             
};
class Maze {
private:
    // Maze dimensions
    int rows, cols;

    CellType** grid; // Dynamic 2D grid storing CellType values
   
    std::mt19937 rng; // Random number generator (used for random maze generation)

    //helper functions
    void allocateGrid();
    // Dynamic memory allocation for the 2D maze grid

    void fillWalls(); 
    // Sets all cells in the maze as walls initially

    bool isInBounds(int r, int c) const; 
    // Checks if a given (row, col) is inside the maze boundary

    void carve(int r, int c); 
    // Recursive maze carving algorithm

public:
    Maze(); // Default Constructor
    // Creates an empty maze object with no grid

    Maze(int r, int c);  // Parameterized Constructor
    // Creates a maze of given size (rows x cols) and initializes grid

    
    Maze(const Maze& other);// Copy Constructor
    // Performs deep copy of the maze grid

    ~Maze();   // Destructor
    // Frees dynamically allocated memory of the maze grid

    Maze& operator=(const Maze& other); // Assignment Operator Overloading

    int getRows() const; // Getter functions for maze size
    int getCols() const;

    char getCell(int r, int c) const; 
    // Used for display and solver logic
   
    void setCell(int r, int c, char val);
    // Updates a maze cell by converting given character into CellType

    void generateMaze();
    // Generates a random maze using carving algorithm.

    void clearVisitedAndPath();
    // Clears only visited cells '.' and solution path '*'

    void display() const;
    // Prints the maze on console using clear symbols
};
#endif