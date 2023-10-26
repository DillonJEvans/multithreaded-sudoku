#ifndef PUZZLE_IO_H_
#define PUZZLE_IO_H_

#include <stdio.h>  // printf, perror, fopen, fscanf, fclose, FILE
#include <stdlib.h> // malloc, free

#define INVALID_PUZZLE (-1)

// Loads the puzzle from the file named filename into the 2D puzzle array.
// Returns the size of the puzzle.
// Returns INVALID_PUZZLE and prints an error message if anything went wrong.
int LoadPuzzle(const char *filename, int ***puzzle);

// Frees the puzzle.
void FreePuzzle(int **puzzle, int size);

// Displays the puzzle.
void DisplayPuzzle(int **puzzle, int size);

#endif // PUZZLE_IO_H_
