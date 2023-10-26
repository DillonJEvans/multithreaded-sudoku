#ifndef IS_COMPLETE_H_
#define IS_COMPLETE_H_

#include <pthread.h> // pthread_t, pthread_create, pthread_join, pthread_exit
#include <stdbool.h> // bool
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free

#include "thread_args.h" // ThreadArgs, THREAD_DEBUG

// Returns true if the puzzle is complete, false otherwise.
bool IsPuzzleComplete(int **puzzle, int size);

// Accepts a ThreadArgs pointer. start is the row to check.
// Sets result to true if the row is complete, false otherwise.
void *IsRowComplete(void *threadArgs);

#endif // IS_COMPLETE_H_
