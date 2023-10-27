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
      printf("%d ", puzzle[row][column]);
    }
    printf("\n");
  }
}

void DisplayPuzzlePretty(int **puzzle, int size)
{
  int digits = 1;
  int tempSize = size;
  while (tempSize >= 10)
  {
    digits++;
    tempSize /= 10;
  }
  int subgridSize = sqrt(size);
  for (int s1 = 0; s1 < subgridSize; s1++)
  {
    for (int s2 = 0; s2 < subgridSize; s2++)
    {
      putc('+', stdout);
      for (int i = 0; i < subgridSize * (digits + 1) + 1; i++)
      {
        putc('-', stdout);
      }
    }
    puts("+");
    for (int r = 0; r < subgridSize; r++)
    {
      for (int subC = 0; subC < subgridSize; subC++)
      {
        putc('|', stdout);
	putc(' ', stdout);
	for (int c = 0; c < subgridSize; c++)
	{
	  if (puzzle[s1 * subgridSize + r][subC * subgridSize + c] == 0)
	  {
            for (int i = 0; i < digits + 1; i++)
	    {
              putc(' ', stdout);
	    }
	  }
	  else
	  {
            printf("%*d ", digits, puzzle[s1 * subgridSize + r][subC * subgridSize + c]);
	
	  }
	}
      }
      puts("|");
    }
  }
  for (int s = 0; s < subgridSize; s++)
  {
    putc('+', stdout);
    for (int i = 0; i < subgridSize * (digits + 1) + 1; i++)
    {
      putc('-', stdout);
    }
  }
  puts("+");
}
