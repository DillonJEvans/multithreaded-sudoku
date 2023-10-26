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

bool SolvePuzzle(int ***puzzle, int size);

void *SolveFromNumber(void *threadArgs);

Cell NextEmptyCell(int **puzzle, int size, Cell current);

void SetCell(int **puzzle, int size, Cell cell);

bool IsCellValid(int **puzzle, int size, Cell cell);

#endif // SOLVE_PUZZLE_H_
