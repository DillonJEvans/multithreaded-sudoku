#include "solve_puzzle.h"

bool SolvePuzzle(int ***puzzle, int size)
{
  ThreadArgs *numbers = malloc(sizeof(*numbers) * size);
  for (int n = 0; n < size; n++)
  {
    numbers[n].puzzle = CopyPuzzle(*puzzle, size);
    numbers[n].size = size;
    numbers[n].start = n + 1;
    pthread_create(&numbers[n].thread, NULL, SolveFromNumber, &numbers[n]);
  }
  bool isSolved = false;
  for (int n = 0; n < size; n++)
  {
    pthread_join(numbers[n].thread, NULL);
    if (numbers[n].result)
    {
      FreePuzzle(*puzzle, size);
      *puzzle = numbers[n].puzzle;
      isSolved = true;
    }
    else
    {
      FreePuzzle(numbers[n].puzzle, size);
    }
  }
  free(numbers);
  return isSolved;
}

void *SolveFromNumber(void *threadArgs)
{
  ThreadArgs *args = threadArgs;
  Cell *stack = malloc(sizeof(*stack) * args->size * args->size);
  int top = 0;
  Cell current = { 0, 0 };
  current = NextEmptyCell(args->puzzle, args->size, current);
  args->puzzle[current.row][current.col] = args->start;
  stack[top] = NextEmptyCell(args->puzzle, args->size, current);
  while (top >= 0 && stack[top].row != args->size)
  {
    SetCell(args->puzzle, args->size, stack[top]);
    if (args->puzzle[stack[top].row][stack[top].col] == 0)
    {
      top--;
    }
    else
    {
      stack[top + 1] = NextEmptyCell(args->puzzle, args->size, stack[top]);
      top++;
    }
  }
  free(stack);
  args->result = (top >= 0);
  pthread_exit(NULL);
}

Cell NextEmptyCell(int **puzzle, int size, Cell current)
{
  while (current.row < size)
  {
    while (current.col < size)
    {
      if (puzzle[current.row][current.col] == 0) return current;
      current.col++;
    }
    current.col = 0;
    current.row++;
  }
  return current;
}

void SetCell(int **puzzle, int size, Cell cell)
{
  while (puzzle[cell.row][cell.col] < size)
  {
    puzzle[cell.row][cell.col]++;
    if (IsCellValid(puzzle, size, cell)) return;
  }
  puzzle[cell.row][cell.col] = 0;
}

bool IsCellValid(int **puzzle, int size, Cell cell)
{
  int number = puzzle[cell.row][cell.col];
  for (int c = 0; c < size; c++)
  {
    if (c != cell.col && puzzle[cell.row][c] == number) return false;
  }
  for (int r = 0; r < size; r++)
  {
    if (r != cell.row && puzzle[r][cell.col] == number) return false;
  }
  int subgridSize = sqrt(size);
  int subgridRow = (cell.row / subgridSize) * subgridSize;
  int subgridCol = (cell.col / subgridSize) * subgridSize;
  for (int r = 0; r < subgridSize; r++)
  {
    for (int c = 0; c < subgridSize; c++)
    {
      if (subgridRow + r == cell.row && subgridCol + c == cell.col) continue;
      if (puzzle[subgridRow + r][subgridCol + c] == number) return false;
    }
  }
  return true;
}
