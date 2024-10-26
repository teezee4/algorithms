/*
 maze_algo.cpp
 Taha Zeeshan
 A recursive algorithm to determine all possible paths through a maze.

 Based on Professor Ross code for maze.cpp
*/
#include <iostream>

using namespace std;
using namespace std::chrono;

#define SIZE 10
//#define DEBUG

// GLOBAL DATA

// a cell type containing a row and column position
// and the compass direction most recently moved
struct cell_type {
   int row;
   int col;
   int dir;    // the most recent compass direction, 'n', 's', 'e', 'w', 0
};
typedef struct cell_type Cell;

// the solution represented as an array of Cells
Cell sol[SIZE * SIZE];

// the maze
int maze[SIZE][SIZE] = {
    1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,1,1,1,
    1,1,1,1,1,0,1,1,1,1,
    1,1,1,1,0,0,0,0,1,1,
    1,1,1,0,0,1,1,0,1,1,
    1,1,1,0,1,1,1,0,1,1,
    1,1,1,0,1,1,1,0,1,1,
    1,1,1,0,0,0,0,0,1,1,
    1,1,1,1,1,1,1,0,0,1,
    1,1,1,1,1,1,1,1,1,1


};

// FUNCTION PROTOTYPES
void build(int);
void printSolution(int);
int is_safe(int);
int getNextCell(int);

int main(void)
{
    auto start = high_resolution_clock::now();
   // set starting position and direction
   sol[0].row = 1;
   sol[0].col = 1;
   sol[0].dir = 0;

   // start recursive solution
   build(0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
     

    cout << duration.count() << endl;
}

/*
A recursive function to determine a path through the maze.
Called for each cell in the solution array.  Finds the next
valid cell to move to, then calls itself for the next cell.
Inside the function, all possible moves for the current cell
are tried before the function returns.
*/
void build(int n)
{
   // loop while there are more possible moves
   while (getNextCell(n)) {

#ifdef DEBUG
      printf("Iteration: %d\tAt: (%d, %d)\t Trying: (%d, %d)\n",
         n, sol[n].row, sol[n].col, sol[n + 1].row, sol[n + 1].col);
#endif
      // check if this possibility is a valid move
      if (is_safe(n)) {

         // is the next possibility the end of the maze?
         if (sol[n + 1].row == SIZE - 2 && sol[n + 1].col == SIZE - 2)
            // print the solution so far
            printSolution(n + 1);
         else
            // get the next move
            build(n + 1);
      }
   }
}

/*
   Outputs the current solution array.
*/
void printSolution(int n)
{
   int i;

   printf("\nA solution was found at:\n");
   for (i = 0; i <= n; i++)
      printf("(%d, %d) ", sol[i].row, sol[i].col);
   printf("\n\n");
}

/*
Determines the next cel to try.  Increments the position
of the next cell and increments the direction of current cell.
Directions are tried in the order east, south, west, north.
*/
int getNextCell(int n)
{
   // set initial position and direction for the next cell
   sol[n + 1].row = sol[n].row;
   sol[n + 1].col = sol[n].col;
   sol[n + 1].dir = 0;

   // try all positions; east, south, west, north
   // increment direction of current cell
   // increment postion of next cell
   switch (sol[n].dir) {
   case 0:
      sol[n].dir = 'e';
      sol[n + 1].col++;
      return 1;
   case 'e':
      sol[n].dir = 's';
      sol[n + 1].row++;
      return 1;
   case 's':
      sol[n].dir = 'w';
      sol[n + 1].col--;
      return 1;
   case 'w':
      sol[n].dir = 'n';
      sol[n + 1].row--;
      return 1;
   case 'n':
      return 0;                // all directions have been tried
   }
   return 0;                    // make compiler happy
}

/*
Looks ahead to checks if a candidate cell is a safe move.
Unsafe moves are cells that are blocked with a wall or current path.
*/
int is_safe(int n)
{
   int i;

   // check if cell is a border cell
   if (maze[sol[n + 1].row][sol[n + 1].col])
      return 0;

   // check if we are attempting to cross our own path
   for (i = 0; i < n; i++)
      // if where we want to go is somewhere we've been...
      if (sol[n + 1].row == sol[i].row && sol[n + 1].col == sol[i].col)
         return 0;

   return 1;
}
