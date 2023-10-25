#include <stdbool.h> // bool
#include <stdio.h>   // fprintf, stderr

#define MAX_PUZZLE_SIZE (16)
#define FILE_BUFFER_SIZE (MAX_PUZZLE_SIZE * 3)

int LoadPuzzle(const char *filename, int **puzzle);

int main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid usage, expected: %s [puzzle_file]\n", argv[0]);
    return 1;
  }
  return 0;
}

// I want a function that accepts the name of a file,
// then opens it, loads it into a grid, and returns that.
// If anything goes wrong, doom ensues.

// \s*(\d+)\s*
//
// If the first line is not <BUFFER_SIZE and only whitespace, an int in range, and more whitespace, doom
// If SIZE is <0, >MAX_SIZE, or not square: doom
// Read the next SIZE lines.
// If not enough lines: doom
// If line too long: doom
// If any of them aren't digits (only digits, whitespace, more digits): doom
// If any of the digits are <0 or >SIZE: doom
// If successfully read SIZE lines, return (don't need to read the whole file).

int LoadPuzzle(const char *filename, int **puzzle)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL) return 0;
  char buffer[FILE_BUFFER_SIZE];
  if (fgets(buffer, FILE_BUFFER_SIZE, file) == NULL) return 0;
  // Read first line in, must be a single int
  // Read from there.
  fclose(file);
  // Return size of the puzzle
}
