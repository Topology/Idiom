#include <stdlib.h>
#include <stdio.h>
#include "trackedmemory.h"

struct _mem_entry{
  void * address;
  size_t bytes;
};

struct _mem_tracker{
struct _mem_entry * entries;
size_t size;
size_t arraySize;
};

typedef struct _mem_entry entry;
typedef struct _mem_tracker tracker;
tracker* t = NULL;

void initialize(){
  if(t == NULL){
    t = malloc(sizeof(tracker));
    t->arraySize = 100;
    t->size = 0;
    t->entries = (entry*)malloc(t->arraySize * sizeof(entry));
  } else if(t->arraySize == t->size){
    t->arraySize *= 2;
    t->entries = (entry*)realloc(t->entries, t->arraySize * sizeof(entry));
  }
}

//inserts in sorted order, lower address gets lower index
void newEntry(void * address, size_t bytes){
  entry e;
  e.address = address;
  e.bytes = bytes;
  size_t pos = t->size;
  //find right position, move entries if needed
  //loop invarient:  t->entries[pos] is empty.
  while(pos > 0){
    if(t->entries[pos-1].address > e.address){
      //entry goes to left, shift element at pos-1 to pos.
      t->entries[pos] = t->entries[pos-1];
      pos--;
    } else {
      //found right position, break out of loop.
      break;
    }
  }
  //pos contains location to insert, data has shifted
  t->entries[pos] = e;
  t->size++;
}


entry * binSearchEntry(entry * entries, size_t minloc,
                       size_t maxloc, void * address){
  if(minloc > maxloc) return NULL;
  if(minloc == maxloc)
    if(entries[minloc].address == address)
      return entries + minloc;
    else
      return NULL;
  if(entries[minloc].address > address) return NULL;
  if(entries[maxloc].address < address) return NULL;
  //target between min and max inclusive.
  size_t midloc = (minloc+maxloc)/2;
  if(entries[midloc].address == address)
    return entries+midloc;  //pointer to match
  if(entries[midloc].address > address){
    if(entries[minloc].address == address)
      return entries+minloc;
    //check between mid-1 and min+1.
    return binSearchEntry(entries, minloc+1, midloc-1, address);
  } else {
    if(entries[maxloc].address == address)
      return entries+maxloc;
    //check between mid+1 and max-1.
    return binSearchEntry(entries, midloc+1, maxloc-1, address);
  }
}

//returns entry in tracker for address
entry * findEntry(void * address){
  //using binary search
  entry * e =  binSearchEntry(t->entries, 0, t->size-1, address);
  if(e != NULL) return e;
  //error could not find entry.  Bad pointer given.
  //exit(-1)
  fprintf(stderr, "Attempted to (free) or (realloc) an inactive pointer.\n");
  exit(-1);
}


void deleteEntryOf(void * address){
  entry * e = findEntry(address);
  int pos = (e- t->entries);
  while(pos < t->size){
    t->entries[pos] = t->entries[pos+1];
    pos++;
  }
  t->size--;
}



void * tmalloc(size_t bytes){
  initialize();
  void * address = malloc(bytes);
  newEntry(address, bytes);
  return address;
}



void * trealloc(void *oldaddress, size_t bytes){
  initialize();
  entry * e =  findEntry(oldaddress);
  void * newaddress = realloc(oldaddress, bytes);
  e->address = newaddress;
  e->bytes = bytes;
  return newaddress;
}


void * tcalloc(size_t number, size_t tsize){
  initialize();
  size_t bytes = number * tsize;
  void * address = calloc(number, tsize);
  newEntry(address, bytes);
  return address;
}


void tfree(void * address){
  initialize();
  deleteEntryOf(address);
  free(address);
}


//return the number of bytes allocated in the heap.
size_t getMemoryUsage(){
  size_t total = 0, i;
  for(i =0; i < t->size; i++){
    total += t->entries[i].bytes;
  }
  return total;
}


//prints error and exits with -1 if memory usage is not 0
void assertNoMemoryLeaks(){
  size_t usage = getMemoryUsage();
  if(usage != 0){
    fprintf(stderr, "MEMORY LEAK:\n");
    fprintf(stderr, "Bytes Allocated: %lu\n", usage);
    fprintf(stderr, "Entries Not Freed: %lu\n", t->size);
    int i;
    for(i = 0; i < t->size; i++)
      free(t->entries[i].address);
    free(t->entries);
    free(t);
    exit(-1);
  }
  free(t->entries);
  free(t);
  t= NULL;
}

//display the contents of the memory tracker.
void printMemoryUsage(){
  initialize();
  entry * stop = t->entries + t->size;// pointer to stop at
  entry * e = t->entries;
  for(e; e < stop; e++)
    printf("%p address, %lu bytes\n", e->address, e->bytes);
}

