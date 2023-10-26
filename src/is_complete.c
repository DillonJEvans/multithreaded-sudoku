#include "is_complete.h"

bool IsPuzzleComplete(int **puzzle, int size)
{
  #ifdef THREAD_DEBUG
    puts("");
  #endif // THREAD_DEBUG
  ThreadArgs *rows = malloc(sizeof(*rows) * size);
  // Create N threads.
  for (int r = 0; r < size; r++)
  {
    rows[r].puzzle = puzzle;
    rows[r].size = size;
    rows[r].start = r;
    pthread_create(&rows[r].thread, NULL, IsRowComplete, &rows[r]);
  }
  bool isComplete = true;
  // Wait for each of the threads to finish.
  for (int r = 0; r < size; r++)
  {
    pthread_join(rows[r].thread, NULL);
    if (!rows[r].result) isComplete = false;
  }
  free(rows);
  #ifdef THREAD_DEBUG
    puts("");
  #endif // THREAD_DEBUG
  return isComplete;
}

void *IsRowComplete(void *threadArgs)
{
  ThreadArgs *args = threadArgs;
  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Row %d: Checking completeness...\n",
           args->thread, args->start);
  #endif // THREAD_DEBUG
  // Check if any of the numbers in the row are 0.
  args->result = true;
  for (int c = 0; c < args->size; c++)
  {
    if (args->puzzle[args->start][c] == 0)
    {
      args->result = false;
      break;
    }
  }
  #ifdef THREAD_DEBUG
    printf("Thread %#016lx, Row %d: %s.\n", args->thread, args->start,
           args->result ? "Complete" : "Not complete");
  #endif // THREAD_DEBUG
  pthread_exit(NULL);
}
