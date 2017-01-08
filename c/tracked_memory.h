#ifndef ___TRACKED_MEMORY_MANAGEMENT___
#define ___TRACKED_MEMORY_MANAGEMENT___

#include<stdlib.h>

//#define TURN_OFF_MEMORY_TRACKING

#ifndef TURN_OFF_MEMORY_TRACKING


#define MALLOC(X) tmalloc(X)
#define REALLOC(X,Y) trealloc(X,Y)
#define CALLOC(X,Y) tcalloc(X,Y)
#define FREE(X) tfree(X)

#else

#define MALLOC(X) malloc(X)
#define REALLOC(X,Y) realloc(X,Y)
#define CALLOC(X,Y) calloc(X,Y)
#define FREE(X) free(X)

#endif


void * tmalloc(size_t);
void * trealloc(void *, size_t);
void * tcalloc(size_t, size_t);
void tfree(void *);
//tracks byte allocation before calling system level functions.

size_t getMemoryUsage();
//return the number of bytes allocated in the heap.

void assertNoMemoryLeaks();
//prints error and exits with -1 if memory usage is not 0

void printMemoryUsage();
//prints every pointer address and number of bytes allocated

#endif
