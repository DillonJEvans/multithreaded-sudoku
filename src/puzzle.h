#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <math.h>   // sqrt
#include <stdio.h>  // printf, perror, fopen, fscanf, fclose, FILE
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

#define INVALID_PUZZLE (-1)

// Loads the puzzle from the file named filename into the 2D puzzle array.
// Returns the size of the puzzle.
// Returns INVALID_PUZZLE and prints an error message if anything went wrong.
int LoadPuzzle(const char *filename, int ***puzzle);

// Returns a copy of the puzzle.
int **CopyPuzzle(int **puzzle, int size);

// Frees the puzzle.
void FreePuzzle(int **puzzle, int size);

// Displays the puzzle.
void DisplayPuzzle(int **puzzle, int size);

// Displays the puzzle.
// Replaces 0s with empty spaces.
// Evenly spaces the numbers.
// Includes borders around the puzzle and around each subgrid.
void DisplayPuzzlePretty(int **puzzle, int size);

// Displays the border between rows for DisplayPuzzlePretty.
void DisplayRowBorder(int subgridSize, int digits);

// Displays n spaces.
void DisplaySpaces(int n);

// Returns the number of digits in the integer n.
int Digits(int n);

#endif // PUZZLE_H_
