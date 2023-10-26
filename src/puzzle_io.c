#include "puzzle_io.h"

int LoadPuzzle(const char *filename,
               int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE])
{
  // Open the file and prepare to begin reading from it.
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    perror(filename);
    return INVALID_PUZZLE;
  }
  // Buffer is for storing the result from fgets.
  char buffer[PUZZLE_BUFFER_SIZE];
  // Current is for looping through the buffer with strtol/StrToInt.
  char *current;

  // Get the size.
  if (!ReadFromFile(buffer, PUZZLE_BUFFER_SIZE, file))
  {
    // There was a problem reading the next line.
    fclose(file);
    return INVALID_PUZZLE;
  }
  current = buffer;
  int size = StrToInt(&current, 1, MAX_PUZZLE_SIZE);
  if (current == NULL)
  {
    // There was a problem getting the size.
    fprintf(stderr, " (size)\n");
    fclose(file);
    return INVALID_PUZZLE;
  }
  int subgridSize = (int) sqrt(size);
  if (subgridSize * subgridSize != size)
  {
    // The size is not a perfect square.
    fprintf(stderr, "%i: size must be a perfect square\n", size);
    fclose(file);
    return INVALID_PUZZLE;
  }

  // Get the puzzle.
  for (int row = 0; row < size; row++)
  {
    // Read the next row into the buffer.
    if (!ReadFromFile(buffer, PUZZLE_BUFFER_SIZE, file))
    {
      // There was a problem reading the next line.
      fclose(file);
      return INVALID_PUZZLE;
    }
    // Prepare to loop through the buffer with strtol/StrToInt.
    current = buffer;
    for (int column = 0; column < size; column++)
    {
      // Get the next value from the buffer.
      int value = StrToInt(&current, 0, size);
      if (current == NULL)
      {
        // There was a problem parsing the next value.
        fprintf(stderr, " (row %i, column %i)\n", row + 1, column + 1);
        fclose(file);
        return INVALID_PUZZLE;
      }
      puzzle[row][column] = value;
    }
  }

  // Valid puzzle. Close the file and return the subgrid size.
  fclose(file);
  return subgridSize;
}

bool ReadFromFile(char *str, int count, FILE *stream)
{
  if (fgets(str, count, stream) != NULL) return true;
  // If the function hasn't returned yet, there is a problem.
  if (feof(stream))
  {
    fprintf(stderr, "Unexpected end of file found\n");
  }
  else
  {
    fprintf(stderr, "Error reading from the file\n");
  }
  return false;
}

int StrToInt(char **str, int minValue, int maxValue)
{
  char *newStr;
  long value = strtol(*str, &newStr, 10);
  // If there was no problem getting the next value, return it.
  if (!(newStr == *str || value < minValue || value > maxValue))
  {
    *str = newStr;
    return value;
  }
  // If the function hasn't returned yet, there was a problem.
  if (newStr == *str)
  {
    fprintf(stderr, "Unexpected character");
  }
  else if (value < minValue)
  {
    fprintf(stderr, "%ld: value cannot be less than %i", value, minValue);
  }
  else
  {
    fprintf(stderr, "%ld: value cannot be greater than %i", value, maxValue);
  }
  // Indicate a problem.
  *str = NULL;
  return 0;
}

void DisplayPuzzle(int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE],
                   int subgridSize)
{
  int size = subgridSize * subgridSize;
  for (int row = 0; row < size; row++)
  {
    for (int column = 0; column < size; column++)
    {
      printf("%i ", puzzle[row][column]);
    }
    printf("\n");
  }
}

void DisplayPuzzlePretty(int puzzle[MAX_PUZZLE_SIZE][MAX_PUZZLE_SIZE],
                         int subgridSize)
{
  DisplayPuzzle(puzzle, subgridSize);
}
