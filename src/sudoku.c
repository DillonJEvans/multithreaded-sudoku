// You can compile either with the build script or the compile line below.
// compile: ./build.sh
// compile: gcc -o sudoku -lpthread -lm src/*.c
//
// run (all):    ./runit
// run (verify): ./sudoku puzzles/puzzle9-valid.txt
// run (hard):   ./sudoku puzzles/puzzle2-difficult.txt
// run (harder): ./sudoku puzzles/challenger-303.txt

#include <stdio.h> // printf, puts, fprintf, stderr

#include "is_complete.h"  // IsPuzzleComplete
#include "is_valid.h"     // IsPuzzleValid
#include "puzzle.h"       // LoadPuzzle, FreePuzzle, DisplayPuzzlePretty
#include "solve_puzzle.h" // SolvePuzzle

int main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid usage, expected: %s [puzzle_file]\n", argv[0]);
    return 1;
  }
  // Load the puzzle.
  int **puzzle;
  int size = LoadPuzzle(argv[1], &puzzle);
  if (size == INVALID_PUZZLE) return 1;
  // Display the puzzle.
  DisplayPuzzlePretty(puzzle, size);
  puts("");
  // Check the puzzle's completeness.
  bool isComplete = IsPuzzleComplete(puzzle, size);
  printf("Complete puzzle? %s\n", isComplete ? "true" : "false");
  // If the puzzle is complete, check it's validity.
  if (isComplete)
  {
    bool isValid = IsPuzzleValid(puzzle, size);
    printf("Valid puzzle? %s\n", isValid ? "true" : "false");
  }
  // Otherwise, attempt to solve the puzzle.
  else
  {
    puts("Solving puzzle...\n");
    bool isSolved = SolvePuzzle(&puzzle, size);
    // If the puzzle was solved, display it.
    if (isSolved)
    {
      DisplayPuzzlePretty(puzzle, size);
    }
    else
    {
      puts("Unsolvable.");
    }
  }
  FreePuzzle(puzzle, size);
  return 0;
}
