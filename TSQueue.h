/*
 * TSQueue.h -- Thread Safe Queue.
 */
#ifndef _TSQUEUE_H_
#define _TSQUEUE_H_
#include "Lock.h"
#include "sthread.h"

const int MAX = 10;

class TSQueue{
  // Synchronization variables
  Lock lock;

  // State variables
  int items[MAX];
  int nFull;
  int firstFull;
  int nextEmpty;

 public: 
  TSQueue();
  ~TSQueue(){};
  bool tryInsert(int item);
  bool tryRemove(int *item);
};
#endif
