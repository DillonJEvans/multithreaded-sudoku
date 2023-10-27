#include "is_valid.h"

bool IsPuzzleValid(int **puzzle, int size)
{
  #ifdef THREAD_DEBUG
    puts("");
  #endif // THREAD_DEBUG

  ThreadArgs *rows = malloc(sizeof(*rows) * size);
  ThreadArgs *columns = malloc(sizeof(*columns) * size);
  ThreadArgs *subgrids = malloc(sizeof(*subgrids) * size);
  // Create N threads to validate the rows.
  for (int r = 0; r < size; r++)
  {
    rows[r].puzzle = puzzle;
    rows[r].size = size;
    rows[r].start = r;
    pthread_create(&rows[r].thread, NULL, IsRowValid, &rows[r]);
  }
  // Create N threads to validate the columns.
  for (int c = 0; c < size; c++)
  {
    columns[c].puzzle = puzzle;
    columns[c].size = size;
    columns[c].start = c;
    pthread_create(&columns[c].thread, NULL, IsColumnValid, &columns[c]);
  }
  // Create N threads to validate the subgrids.
  for (int s = 0; s < size; s++)
  {
    subgrids[s].puzzle = puzzle;
    subgrids[s].size = size;
    subgrids[s].start = s;
    pthread_create(&subgrids[s].thread, NULL, IsSubgridValid, &subgrids[s]);
  }
  bool isValid = true;
  // Wait for each of the row threads to finish.
  for (int r = 0; r < size; r++)
  {
    pthread_join(rows[r].thread, NULL);
    if (!rows[r].result) isValid = false;
  }
  // Wait for each of the column threads to finish.
  for (int c = 0; c < size; c++)
  {
    pthread_join(columns[c].thread, NULL);
    if (!columns[c].result) isValid = false;
  }
  // Wait for each of the subgrid threads to finish.
  for (int s = 0; s < size; s++)
  {
    pthread_join(subgrids[s].thread, NULL);
    if (!subgrids[s].result) isValid = false;
  }
  free(rows);
  free(columns);
  free(subgrids);

  #ifdef THREAD_DEBUG
    puts("");
  #endif // THREAD_DEBUG
  return isValid;
}

void *IsRowValid(void *threadArgs)
{
  ThreadArgs *args = threadArgs;
  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Row %2d: Checking validity...\n",
           args->thread, args->start);
  #endif // THREAD_DEBUG

  args->result = true;
  // An array of which number are present in the row.
  bool *numbers = malloc(sizeof(*numbers) * (args->size + 1));
  memset(numbers, false, sizeof(*numbers) * (args->size + 1));
  for (int c = 0; c < args->size; c++)
  {
    int number = args->puzzle[args->start][c];
    // If this number is already present in the row, return false.
    if (numbers[number])
    {
      args->result = false;
      break;
    }
    // Mark the number as present in the row.
    numbers[number] = true;
  }
  free(numbers);

  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Row %2d: %s.\n", args->thread, args->start,
           args->result ? "Valid" : "Not valid");
  #endif // THREAD_DEBUG
  pthread_exit(NULL);
}

void *IsColumnValid(void *threadArgs)
{
  ThreadArgs *args = threadArgs;
  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Col %2d: Checking validity...\n",
           args->thread, args->start);
  #endif // THREAD_DEBUG

  args->result = true;
  // An array of which number are present in the column.
  bool *numbers = malloc(sizeof(*numbers) * (args->size + 1));
  memset(numbers, false, sizeof(*numbers) * (args->size + 1));
  for (int r = 0; r < args->size; r++)
  {
    int number = args->puzzle[r][args->start];
    // If this number is already present in the column, return false.
    if (numbers[number])
    {
      args->result = false;
      break;
    }
    // Mark the number as present in the column.
    numbers[number] = true;
  }
  free(numbers);

  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Col %2d: %s.\n", args->thread, args->start,
           args->result ? "Valid" : "Not valid");
  #endif // THREAD_DEBUG
  pthread_exit(NULL);
}

void *IsSubgridValid(void *threadArgs)
{
  ThreadArgs *args = threadArgs;
  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Sub %2d: Checking validity...\n",
           args->thread, args->start);
  #endif // THREAD_DEBUG

  args->result = true;
  // An array of which number are present in the subgrid.
  bool *numbers = malloc(sizeof(*numbers) * (args->size + 1));
  memset(numbers, false, sizeof(*numbers) * (args->size + 1));
  // Calculate the row and column of the top-left number in the subgrid.
  int subgridSize = sqrt(args->size);
  int subgridRow = (args->start / subgridSize) * subgridSize;
  int subgridCol = (args->start % subgridSize) * subgridSize;
  for (int r = 0; r < subgridSize; r++)
  {
    for (int c = 0; c < subgridSize; c++)
    {
      int number = args->puzzle[subgridRow + r][subgridCol + c];
      // If this number is already present in the subgrid, return false.
      if (numbers[number]) args->result = false;
      // Mark the number as present in the subgrid.
      numbers[number] = true;
    }
  }
  free(numbers);

  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Sub %2d: %s.\n", args->thread, args->start,
           args->result ? "Valid" : "Not valid");
  #endif // THREAD_DEBUG
  pthread_exit(NULL);
}
