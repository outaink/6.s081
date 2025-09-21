# xv6 Code Style and Conventions

## C Code Style
- **Indentation**: 2 spaces (no tabs)
- **Brace Style**: K&R style - opening brace on same line for functions
- **Function Return Type**: On separate line before function name
- **Comments**: Minimal, inline comments aligned, focus on clarity through code
- **Line Length**: Generally kept under 80 characters
- **Variable Names**: Short, descriptive lowercase with underscores (e.g., `proc`, `cpu_id`)

## Naming Conventions
- **Functions**: lowercase with underscores (e.g., `procinit()`, `trap_init()`)
- **Macros/Constants**: UPPERCASE (e.g., `MAXOPBLOCKS`, `NCPU`)
- **Struct Members**: lowercase, concise names
- **Global Variables**: Simple lowercase names
- **File Names**: All lowercase, no underscores in kernel files

## Code Organization
- **Headers**: Function declarations in defs.h or specific .h files
- **No C++ Features**: Pure ANSI C only
- **Error Handling**: Use panic() for kernel errors, return -1 for user errors
- **Memory**: Explicit allocation/deallocation, no garbage collection

## Compilation Flags
```
CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
```
- All warnings are errors (-Werror)
- Debug symbols included (-ggdb)
- Frame pointers preserved for debugging

## Assembly Style
- AT&T syntax for RISC-V assembly
- Comments use # or //
- Labels are lowercase with colons