# xv6 Codebase Structure

## Directory Layout

### `/kernel` - Kernel Source Code
Core operating system implementation:
- **Boot & Init**: `entry.S`, `start.c`, `main.c`
- **Memory Management**: `kalloc.c`, `vm.c`
- **Process Management**: `proc.c`, `proc.h`, `exec.c`, `swtch.S`
- **Trap Handling**: `trap.c`, `trampoline.S`, `kernelvec.S`, `syscall.c`
- **File System**: `fs.c`, `fs.h`, `bio.c`, `log.c`, `file.c`
- **Device Drivers**: `console.c`, `uart.c`, `virtio_disk.c`, `plic.c`
- **Synchronization**: `spinlock.c`, `sleeplock.c`
- **System Calls**: `sysproc.c`, `sysfile.c`

### `/user` - User Programs
User space programs and libraries:
- **Shell**: `sh.c` - command line interface
- **Utilities**: `ls.c`, `cat.c`, `echo.c`, `grep.c`, `mkdir.c`, `rm.c`, etc.
- **User Library**: `ulib.c`, `umalloc.c`, `printf.c`
- **Tests**: `usertests.c`, `alarmtest.c`, `bttest.c`
- **System Call Stubs**: Generated from `usys.pl`

### `/mkfs` - File System Creator
- `mkfs.c` - Creates the initial file system image

### Root Files
- `Makefile` - Build configuration
- `README` - Project documentation
- Configuration files: `.gitignore`, `.gdbinit.tmpl-riscv`

## Key Header Files
- `kernel/types.h` - Basic type definitions
- `kernel/param.h` - System parameters
- `kernel/memlayout.h` - Memory layout constants
- `kernel/riscv.h` - RISC-V specific definitions
- `kernel/defs.h` - Function declarations
- `user/user.h` - User program interface