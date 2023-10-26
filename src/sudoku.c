#include <stdio.h> // fprintf, stderr

#include "is_complete.h" // IsPuzzleComplete
#include "puzzle_io.h"   // LoadPuzzle, FreePuzzle, DisplayPuzzle

int main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid usage, expected: %s [puzzle_file]\n", argv[0]);
    return 1;
  }
  int **puzzle;
  int size = LoadPuzzle(argv[1], &puzzle);
  if (size == INVALID_PUZZLE) return 1;
  DisplayPuzzle(puzzle, size);
  bool IsComplete = IsPuzzleComplete(puzzle, size);
  printf("Complete puzzle? ");
  puts(IsComplete ? "true" : "false");
  FreePuzzle(puzzle, size);
  return 0;
}
