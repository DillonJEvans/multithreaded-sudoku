#include "puzzle.h"

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
      printf("%d ", puzzle[row][column]);
    }
    printf("\n");
  }
}

void DisplayPuzzlePretty(int **puzzle, int size)
{
  int digits = Digits(size);
  int subgridSize = sqrt(size);
  // Loop through the subgrids vertically.
  for (int sr = 0; sr < subgridSize; sr++)
  {
    DisplayRowBorder(subgridSize, digits);
    // Loop through the rows in the subgrid.
    for (int r = 0; r < subgridSize; r++)
    {
      // Loop through the subgrids horizontally.
      for (int sc = 0; sc < subgridSize; sc++)
      {
        putc('|', stdout);
        putc(' ', stdout);
        // Loop through the columns in the subgrid.
        for (int c = 0; c < subgridSize; c++)
        {
          // Display the number (or spaces if it is 0).
          int row = sr * subgridSize + r;
          int col = sc * subgridSize + c;
          int number = puzzle[row][col];
          if (number == 0) DisplaySpaces(digits + 1);
          else printf("%*d ", digits, number);
        }
      }
      puts("|");
    }
  }
  DisplayRowBorder(subgridSize, digits);
}

void DisplayRowBorder(int subgridSize, int digits)
{
  int dashes = subgridSize * (digits + 1) + 1;
  for (int s = 0; s < subgridSize; s++)
  {
    putc('+', stdout);
    for (int d = 0; d < dashes; d++)
    {
      putc('-', stdout);
    }
  }
  puts("+");
}

void DisplaySpaces(int n)
{
  for (int i = 0; i < n; i++)
  {
    putc(' ', stdout);
  }
}

int Digits(int n)
{
  int digits = 1;
  while (n >= 10)
  {
    digits++;
    n /= 10;
  }
  return digits;
}
