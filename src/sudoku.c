#include <stdio.h> // fprintf, stderr

#include "puzzle_io.h" // LoadPuzzle, DisplayPuzzle

int main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid usage, expected: %s [puzzle_file]\n", argv[0]);
    return 1;
  }
  int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE];
  int subgridSize = LoadPuzzle(argv[1], puzzle);
  if (subgridSize == INVALID_PUZZLE)
  {
    return 1;
  }
  DisplayPuzzle(puzzle, subgridSize);
  return 0;
}
