#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "mmu.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "mutex.h"

void macquire(mutex *m)
{
  acquire(&m->lock);
  struct proc *current_process = myproc();
  uint *list = current_process->holding;
  pde_t *currentProcessPageDir = current_process->pgdir;
  pte_t *v_addr = walkpgdir(currentProcessPageDir, (const void *)m, 0);
  int size = 16;
  int lockIndex;
  for (lockIndex = 0; lockIndex < size; lockIndex++)
  {
    uint currentLock = list[lockIndex];
    if (currentLock == 0)
    {
      currentLock = V2P(v_addr);
      break;
    }
  }

  while (m->isLocked)
  {
    sleep(m, &m->lock);
  }

  m->procId = current_process->pid;
  m->isLocked = 1;

  release(&m->lock);
}

void mrelease(mutex *m)
{
  acquire(&m->lock);
  m->isLocked = 0;
  m->procId = 0;

  struct proc *current_process = myproc();
  uint *list = current_process->holding;
  pde_t *currentProcessPageDir = current_process->pgdir;
  pte_t *v_addr = walkpgdir(currentProcessPageDir, (const void *)m, 0);
  int lockIndex;
  int size = 16;
  for (lockIndex = 0; lockIndex < size; lockIndex++)
  {
    uint currentLock = list[lockIndex];
    if (currentLock == V2P(v_addr))
    {
      currentLock = 0;
      break;
    }
  }
  wakeup(m);
  release(&m->lock);
}
