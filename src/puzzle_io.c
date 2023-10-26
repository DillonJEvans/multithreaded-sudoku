#include "puzzle_io.h"

int LoadPuzzle(const char *filename, int ***puzzle)
{
  // Open the file and prepare to begin reading from it.
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    perror(filename);
    return INVALID_PUZZLE;
  }
  // Get the size.
  int size;
  fscanf(file, "%d", &size);
  // Create the array of rows.
  *puzzle = malloc(sizeof(**puzzle) * size);
  // Read in each row.
  for (int r = 0; r < size; r++)
  {
    // Create the row.
    int *row = malloc(sizeof(*row) * size);
    for (int c = 0; c < size; c++)
    {
      fscanf(file, "%d", &row[c]);
    }
    (*puzzle)[r] = row;
  }
  fclose(file);
  return size;
}

int **CopyPuzzle(int **puzzle, int size)
{
  int **copy = malloc(sizeof(*copy) * size);
  for (int r = 0; r < size; r++)
  {
    int *row = malloc(sizeof(*row) * size);
    memcpy(row, puzzle[r], sizeof(*row) * size);
    copy[r] = row;
  }
  return copy;
}

void FreePuzzle(int **puzzle, int size)
{
  for (int row = 0; row < size; row++)
  {
    free(puzzle[row]);
  }
  free(puzzle);
}

void DisplayPuzzle(int **puzzle, int size)
{
  for (int row = 0; row < size; row++)
  {
    for (int column = 0; column < size; column++)
    {
      printf("%i ", puzzle[row][column]);
    }
    printf("\n");
  }
}
