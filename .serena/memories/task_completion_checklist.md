# Task Completion Checklist for xv6

## Before Committing Code

### 1. Build Verification
- [ ] Run `make clean` to ensure clean build
- [ ] Run `make` to verify compilation without errors
- [ ] Check for compiler warnings (all warnings are errors with -Werror)

### 2. Testing
- [ ] Run `make qemu` to test basic functionality
- [ ] Test the specific feature/fix implemented
- [ ] Run `make grade` if working on a lab assignment
- [ ] Verify no regressions in existing functionality

### 3. Code Quality
- [ ] Follow xv6 coding style (2-space indent, K&R braces)
- [ ] Keep lines under 80 characters where possible
- [ ] Use descriptive but concise variable names
- [ ] Add minimal, clear comments only where necessary
- [ ] Ensure no memory leaks or resource leaks

### 4. RISC-V Specific
- [ ] Verify trap handling if modified
- [ ] Check interrupt disable/enable pairs
- [ ] Ensure proper memory barriers where needed

### 5. Documentation
- [ ] Update relevant comments if behavior changes
- [ ] Document any new system calls or interfaces

## Common Issues to Check
- Stack overflow in kernel (limited kernel stack)
- Race conditions in concurrent code
- Proper lock acquisition order
- Resource cleanup on error paths
- Integer overflow in calculations