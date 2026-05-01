#ifndef SOLVER_H  // Prevent the file from being included more than once 
#define SOLVER_H  //Avoids duplicate definition errors during compilation

#include "Maze.h" //The solver uses the Maze class, so it must know its definition
#include "Exceptions.h" 

class MazeSolver {
private:
    Maze* mazePtr; //Stores a pointer to a Maze object
                   //The solver does not own the maze — it just works on it
    bool dfs(int r, int c); //Depth‑First Search
    //rows and columns, returns true if a path to the exit is found
    //kept private because it’s only used internally by solve()

public:
    MazeSolver(Maze* m); //Called when a MazeSolver object is created
                         //Takes a pointer to a Maze
                         //Initializes mazePtr
    bool solve();
};

#endif