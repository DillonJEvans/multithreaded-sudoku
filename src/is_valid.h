#ifndef IS_VALID_H_
#define IS_VALID_H_

#include <math.h>    // sqrt
#include <pthread.h> // pthread_create, pthread_join, pthread_exit
#include <stdbool.h> // bool
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free
#include <string.h>  // memset

#include "thread_args.h" // ThreadArgs, THREAD_DEBUG

bool IsPuzzleValid(int **puzzle, int size);

void *IsRowValid(void *threadArgs);
void *IsColumnValid(void *threadArgs);
void *IsSubgridValid(void *threadArgs);

#endif // IS_VALID_H_
