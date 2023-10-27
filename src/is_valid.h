#ifndef IS_VALID_H_
#define IS_VALID_H_

#include <math.h>    // sqrt
#include <pthread.h> // pthread_create, pthread_join, pthread_exit
#include <stdbool.h> // bool
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free
#include <string.h>  // memset

#include "thread_args.h" // ThreadArgs, THREAD_DEBUG

// Returns true if the puzzle is valid, false otherwise.
bool IsPuzzleValid(int **puzzle, int size);

// Accepts a ThreadArgs pointer. start is the row to check.
// Sets result to true if the row is valid, false otherwise.
void *IsRowValid(void *threadArgs);

// Accepts a ThreadArgs pointer. start is the column to check.
// Sets result to true if the column is valid, false otherwise.
void *IsColumnValid(void *threadArgs);

// Accepts a ThreadArgs pointer. start is the subgrid to check.
// Sets result to true if the subgrid is valid, false otherwise.
void *IsSubgridValid(void *threadArgs);

#endif // IS_VALID_H_
