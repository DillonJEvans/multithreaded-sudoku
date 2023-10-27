#include "solve_puzzle.h"

bool SolvePuzzle(int ***puzzle, int size)
{
  #ifdef THREAD_DEBUG
    puts("");
  #endif // THREAD_DEBUG

  ThreadArgs *numbers = malloc(sizeof(*numbers) * size);
  // Create N threads to check each first number.
  for (int n = 0; n < size; n++)
  {
    numbers[n].puzzle = CopyPuzzle(*puzzle, size);
    numbers[n].size = size;
    numbers[n].start = n + 1;
    pthread_create(&numbers[n].thread, NULL, SolveFromNumber, &numbers[n]);
  }
  bool isSolved = false;
  // Wait for each of the threads to finish.
  for (int n = 0; n < size; n++)
  {
    pthread_join(numbers[n].thread, NULL);
    // If the thread solved the puzzle,
    // free puzzle and then steal the thread's puzzle.
    if (numbers[n].result)
    {
      FreePuzzle(*puzzle, size);
      *puzzle = numbers[n].puzzle;
      isSolved = true;
    }
    // Otherwise, free the thread's puzzle.
    else
    {
      FreePuzzle(numbers[n].puzzle, size);
    }
  }
  free(numbers);

  #ifdef THREAD_DEBUG
    puts("");
  #endif // THREAD_DEBUG
  return isSolved;
}

void *SolveFromNumber(void *threadArgs)
{
  ThreadArgs *args = threadArgs;
  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Num %2d: Solving puzzle...\n",
           args->thread, args->start);
  #endif // THREAD_DEBUG

  // Set the first empty cell to the starting number given.
  Cell current = { 0, 0 };
  current = NextEmptyCell(args->puzzle, args->size, current);
  args->puzzle[current.row][current.col] = args->start;
  // If the first empty cell cannot be the starting number given, return false.
  if (!IsCellValid(args->puzzle, args->size, current))
  {
    args->result = false;
    #ifdef THREAD_DEBUG
      printf("Thread %#016lx, Num %2d: %s.\n", args->thread, args->start,
             args->result ? "Solved" : "Not solved");
    #endif // THREAD_DEBUG
    pthread_exit(NULL);
  }
  // Store previously filled in cells on a stack.
  Cell *stack = malloc(sizeof(*stack) * args->size * args->size);
  int top = 0;
  // Get the second empty cell as the top of the stack.
  stack[top] = NextEmptyCell(args->puzzle, args->size, current);
  // Loop until either the stack exhausts (unsolved)
  // or the end of the puzzle is reached (solved).
  while (top >= 0 && stack[top].row != args->size)
  {
    // Set the number of the cell on the top of the stack.
    SetCell(args->puzzle, args->size, stack[top]);
    // If there is no valid number for the top cell, pop it off of the stack.
    // (AKA backtrack to the last filled in cell).
    if (args->puzzle[stack[top].row][stack[top].col] == 0)
    {
      top--;
    }
    // Otherwise, advance to the next empty cell, pushing it to the stack.
    else
    {
      stack[top + 1] = NextEmptyCell(args->puzzle, args->size, stack[top]);
      top++;
    }
  }
  free(stack);
  // If the stack is not empty, the puzzle was solved.
  args->result = (top >= 0);

  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Num %2d: %s.\n", args->thread, args->start,
           args->result ? "Solved" : "Not solved");
  #endif // THREAD_DEBUG
  pthread_exit(NULL);
}

Cell NextEmptyCell(int **puzzle, int size, Cell current)
{
  while (current.row < size)
  {
    while (current.col < size)
    {
      // Return the cell if it is empty.
      if (puzzle[current.row][current.col] == 0) return current;
      current.col++;
    }
    current.col = 0;
    current.row++;
  }
  // This will a cell with row equal to size
  // if the end of the puzzle is reached.
  return current;
}

void SetCell(int **puzzle, int size, Cell cell)
{
  while (puzzle[cell.row][cell.col] < size)
  {
    puzzle[cell.row][cell.col]++;
    if (IsCellValid(puzzle, size, cell)) return;
  }
  // If no valid number could be found, clear the cell.
  puzzle[cell.row][cell.col] = 0;
}

bool IsCellValid(int **puzzle, int size, Cell cell)
{
  int number = puzzle[cell.row][cell.col];
  // Make sure the number is unique to it's row.
  for (int c = 0; c < size; c++)
  {
    if (c != cell.col && puzzle[cell.row][c] == number) return false;
  }
  // Make sure the number is unique to it's column.
  for (int r = 0; r < size; r++)
  {
    if (r != cell.row && puzzle[r][cell.col] == number) return false;
  }
  // Make sure the number is unique to it's subgrid.
  int subgridSize = sqrt(size);
  int subgridRow = (cell.row / subgridSize) * subgridSize;
  int subgridCol = (cell.col / subgridSize) * subgridSize;
  for (int r = 0; r < subgridSize; r++)
  {
    for (int c = 0; c < subgridSize; c++)
    {
      // Don't match the cell to itself.
      if (subgridRow + r == cell.row && subgridCol + c == cell.col) continue;
      if (puzzle[subgridRow + r][subgridCol + c] == number) return false;
    }
  }
  return true;
}
