// 系统信息结构体
// 用于 sysinfo 系统调用返回系统状态信息
struct sysinfo {
  uint64 freemem;   // 空闲内存大小（字节）
  uint64 nproc;     // 当前活动进程数量（非UNUSED状态）
};
