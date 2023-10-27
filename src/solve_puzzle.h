#ifndef SOLVE_PUZZLE_H_
#define SOLVE_PUZZLE_H_

#include <math.h>    // sqrt
#include <pthread.h> // pthread_create, pthread_join, pthread_exit
#include <stdbool.h> // bool
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

#include <string.h>  // memset

#include "puzzle_io.h"   // CopyPuzzle, FreePuzzle
#include "thread_args.h" // ThreadArgs, THREAD_DEBUG

typedef struct
{
  int row;
  int col;
} Cell;

// Solves the puzzle, changing it and the pointer to it.
// Returns true if the puzzle was solved, false otherwise.
bool SolvePuzzle(int ***puzzle, int size);

// Accepts a ThreadArgs pointer. start is the first number to fill in.
// Sets result to true if the puzzle is solved, false otherwise.
void *SolveFromNumber(void *threadArgs);

// Returns the next empty cell in the puzzle, starting from current.
// Returns a cell with a row equal to size if there is no more empty cells.
Cell NextEmptyCell(int **puzzle, int size, Cell current);

// Increments the number at the cell until it finds a number that doesn't
// invalidate the puzzle.
void SetCell(int **puzzle, int size, Cell cell);

// Returns true if the number in the cell is valid, false otherwise.
bool IsCellValid(int **puzzle, int size, Cell cell);

#endif // SOLVE_PUZZLE_H_
