#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// 系统调用: trace(int mask)
// 功能: 设置当前进程的系统调用跟踪掩码
// 参数: mask - 位掩码，每一位对应一个系统调用号，为1表示需要跟踪该系统调用
// 返回值: 成功返回0，失败返回-1
uint64
sys_trace(void)
{
  int trace_mask;
  struct proc *current_proc = myproc();

  // 从用户空间获取第一个参数（掩码值）
  // argint(0, ...) 表示获取第0个参数（索引从0开始）
  if (argint(0, &trace_mask) < 0) {
    // 参数获取失败，返回错误
    return -1;
  }

  // 设置当前进程的系统调用跟踪掩码
  // 该掩码会被子进程继承
  current_proc->syscall_trace_mask = trace_mask;
  
  return 0;  // 成功设置跟踪掩码
}

// 系统调用: sysinfo(struct sysinfo *info)
// 功能: 收集当前系统状态信息并返回给用户空间
// 参数: info - 用户空间的 sysinfo 结构体指针，用于存储系统信息
// 返回值: 成功返回0，失败返回-1
uint64
sys_sysinfo(void) {
  struct sysinfo kernel_info;
  struct proc *current_proc = myproc();
  
  // 收集系统信息
  mh_freebytes(&kernel_info.freemem);   // 统计空闲内存大小
  mh_procnum(&kernel_info.nproc);       // 统计活动进程数量

  // 从用户空间获取第一个参数（info 结构体的地址）
  uint64 user_info_addr;
  if (argaddr(0, &user_info_addr) < 0) {
    // 参数获取失败
    return -1;
  }

  // 将内核空间的系统信息拷贝到用户空间
  // copyout: 从内核地址空间复制数据到用户地址空间
  if (copyout(current_proc->pagetable, user_info_addr, 
              (char*)&kernel_info, sizeof(kernel_info)) < 0) {
    // 数据拷贝失败（可能是地址无效或无权访问）
    return -1;
  }

  return 0;  // 成功返回系统信息
}