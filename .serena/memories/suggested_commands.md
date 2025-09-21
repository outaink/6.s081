# xv6 Development Commands

## Building and Running
- `make` - Build the kernel and user programs
- `make qemu` - Build and run xv6 in QEMU emulator
- `make clean` - Clean build artifacts
- `make fs.img` - Build the file system image

## Testing and Grading
- `make grade` - Run the grading script for the current lab
- `./grade-lab-traps` - Run the specific grading script for traps lab
- Python test scripts use the gradelib.py framework

## QEMU Control
- `Ctrl-a x` - Exit QEMU
- `Ctrl-a c` - Enter QEMU monitor
- `Ctrl-p` - Print process list in xv6

## Debugging
- `make qemu-gdb` - Start QEMU in debug mode
- `gdb-multiarch` or `riscv64-unknown-elf-gdb` - Connect debugger

## Common Development Workflow
1. Edit source files in kernel/ or user/
2. Run `make clean` if changing headers
3. Run `make qemu` to test
4. Run `make grade` to verify lab requirements

## System Commands
- `git status` - Check version control status
- `git diff` - View uncommitted changes
- `ls -la` - List files with details
- `grep -r "pattern" .` - Search for patterns in code