/*
 * TSQueue.cc -- Thread Safe Queue.
 */
#include <assert.h>
#include "sthread.h"
#include "Lock.h"
#include "TSQueue.h"

TSQueue::TSQueue()
{
  nFull = 0;
  firstFull = 0;
  nextEmpty = 0;
}


// Attempt to insert an item. Return true on success.
// If the queue is full, return false.
bool 
TSQueue::tryInsert(int item)
{
  bool ret = false;
  lock.Acquire();
  if(nFull < MAX){
    items[nextEmpty] = item;
    nFull++;
    nextEmpty = (nextEmpty + 1) % MAX;
    ret = true;
  }
  lock.Release();
  return ret;
}

// Attempt to remove an item. Return true on success.
// If the queue is empty,return false.
bool 
TSQueue::tryRemove(int *item)
{
  bool ret = false;
  lock.Acquire();
  if(nFull > 0){
    *item = items[firstFull];
    nFull--;
    firstFull = (firstFull + 1) % MAX;
    ret = true;
  }
  lock.Release();
  return ret;
}

