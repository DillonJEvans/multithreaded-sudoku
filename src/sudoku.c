#include <stdio.h> // fprintf, stderr

#include "is_complete.h"  // IsPuzzleComplete
#include "is_valid.h"     // IsPuzzleValid
#include "puzzle.h"       // LoadPuzzle, FreePuzzle, DisplayPuzzle
#include "solve_puzzle.h" // SolvePuzzle

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
  DisplayPuzzlePretty(puzzle, size);
  bool isComplete = IsPuzzleComplete(puzzle, size);
  printf("Complete puzzle? ");
  puts(isComplete ? "true" : "false");
  if (isComplete)
  {
    bool isValid = IsPuzzleValid(puzzle, size);
    printf("Valid puzzle? ");
    puts(isValid ? "true" : "false");
  }
  else
  {
    bool isSolved = SolvePuzzle(&puzzle, size);
    if (isSolved)
    {
      DisplayPuzzlePretty(puzzle, size);
    }
    else
    {
      printf("Unsolvable\n");
    }
  }
  FreePuzzle(puzzle, size);
  return 0;
}
