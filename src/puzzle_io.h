#ifndef PUZZLE_IO_H_
#define PUZZLE_IO_H_

#include <math.h>    // sqrt
#include <stdbool.h> // bool
#include <stdio.h>   // printf, fprintf, fopen, fgets, fclose, feof, ferror,
                     // perror, FILE, stderr
#include <stdlib.h>  // strtol

#define MAX_PUZZLE_SIZE (16)
#define PUZZLE_BUFFER_SIZE (MAX_PUZZLE_SIZE * 3)

#define INVALID_PUZZLE (-1)

// Loads the puzzle in the file named filename into the 2D puzzle array.
// Returns the size of subgrids in the puzzle.
// E.g. a 4x4 puzzle returns 2, a 9x9 puzzle returns 3, etc.
// Returns INVALID_PUZZLE and prints an error message
// if there was a problem loading the puzzle.
int LoadPuzzle(const char *filename,
               int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE]);

// Reads the next line of the stream (via fgets) into the str.
// Returns true if there were no problems.
// Returns false and prints an error message if there was a problem.
bool ReadFromFile(char *str, int count, FILE *stream);

// Converts the string at *str to an int (via strtol).
// Returns the int and moves *str to point to the character after the int.
// If strtol fails or the value is not in the given range,
// then *str will be set to NULL.
int StrToInt(char **str, int minValue, int maxValue);

// Displays the puzzle.
void DisplayPuzzle(int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE],
                   int subgridSize);

// Displays the puzzle.
// Evenly spaces the numbers,
// and includes borders around the puzzle and between subgrids.
// Not yet implemented.
void DisplayPuzzlePretty(int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE],
                         int subgridSize);

#endif // PUZZLE_IO_H_
