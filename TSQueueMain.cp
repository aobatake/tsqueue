#include <assert.h>
#include <stdio.h>
#include "sthread.h"
#include "TSQueue.h"


void *putSome(void *tsqueuePtr)
{
  int ii;
  TSQueue *queue = (TSQueue *)tsqueuePtr;

  for(ii = 0; ii < 50; ii++){
    queue->tryInsert(ii);
  }
  return NULL;
}  


int main(int argc, char **argv)
{
  TSQueue *queues[3];
  sthread_t workers[3];
  int ii, jj, ret;
  bool success;

  // Start the worker threads
  for(ii = 0; ii < 3; ii++){
    queues[ii] = new TSQueue();
    sthread_create_p(&workers[ii], putSome, 
                     queues[ii]);
  }

  sthread_join(workers[0]);

  // Remove from the queues
  for(ii = 0; ii < 3; ii++){
    printf("Queue %d:\n", ii);
    for(jj = 0; jj < 20; jj++){
      success = queues[ii]->tryRemove(&ret);
      if(success){
        printf("Removed %d\n", ret);
      }
      else{
        printf("Nothing there\n");
      }
    }
  }
}
