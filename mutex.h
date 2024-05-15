#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "spinlock.h"

typedef struct
{
  int procId;
  struct spinlock lock;
  uint isLocked;
} mutex;

#endif
