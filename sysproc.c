#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "mutex.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  if (n == 0)
  {
    yield();
    return 0;
  }
  acquire(&tickslock);
  ticks0 = ticks;
  myproc()->sleepticks = n;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  myproc()->sleepticks = -1;
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

void
sys_macquire(void)
{
  mutex* lock;
  int zero = 0;
  if (argptr(0, (char **)&lock, sizeof(mutex))<zero) {
    return;
  }
  macquire(lock);
} 

void
sys_mrelease(void)
{
  mutex* lock;
  int zero = 0;
  if (argptr(zero, (char **)&lock, sizeof(mutex)) < zero) {
    return;
  }
  mrelease(lock);
}

int 
sys_clone(void)
{
  int args;
  int firstarg;
  int st;
  argint(0, &firstarg);
  argint(1, &st);
  argint(2, &args);
  return clone((void (*)(void*))firstarg, (void*)st, (void*)args);
}
int
sys_nice(void)
{
  int c;
  int err = -1;
  int zero = 0;
  int cap = -20;
  if (argint(zero, &c) < zero) {
    return err;
  }
  struct proc *curproc = myproc();
  int vlad = curproc->nice + c;

  if (vlad < cap) {
    vlad = cap;
  } else if (vlad > 19) {
    vlad = 19;
  }
  curproc->nice = vlad;
  return zero;
}
