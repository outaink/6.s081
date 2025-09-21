# xv6 Operating System - MIT 6.S081

## Project Purpose
xv6 is a teaching operating system for MIT's 6.S081 course. It's a re-implementation of Unix Version 6 (v6) for modern RISC-V multiprocessor architecture using ANSI C. The project serves as a simplified operating system for educational purposes.

## Tech Stack
- **Language**: ANSI C
- **Architecture**: RISC-V 64-bit
- **Toolchain**: riscv64-unknown-elf-gcc or riscv64-linux-gnu-gcc
- **Emulator**: QEMU (qemu-system-riscv64)
- **Build System**: GNU Make
- **Assembly**: RISC-V assembly for low-level operations

## Current Lab
The repository is currently on the "traps" lab (LAB=traps in conf/lab.mk), focusing on trap handling and system calls.

## Key Features
- Process management and scheduling
- Virtual memory with paging
- File system implementation
- Device drivers (UART, disk, console)
- System calls and trap handling
- Interrupt handling (PLIC)
- Synchronization primitives (spinlocks, sleeplocks)