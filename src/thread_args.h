#ifndef THREAD_ARGS_H_
#define THREAD_ARGS_H_

#include <pthread.h> // pthread_t
#include <stdbool.h> // bool

typedef struct
{
  pthread_t thread; // The thread ID.
  int **puzzle;     // The puzzle.
  int size;         // The size of the puzzle.
  int start;        // Where to start (e.g. row #)
  bool result;      // Return value of the thread.
} ThreadArgs;

// If THREAD_DEBUG is defined, threads will print their status.
#define THREAD_DEBUG

#endif // THREAD_ARGS_H
