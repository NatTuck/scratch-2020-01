
# CS5600: Lecture 3

## In case you missed it

Course website + syllabus is linked from: http://khoury.neu.edu/home/ntuck

## Today: Wrapping up assembly basics

## Calling Conventions

 - What the C compiler does translating C to ASM.
 
### amd64 (64-bit)

 - Arguments are passed:
   - %rdi, %rsi, %rdx, %rcx, %r8, %r9
   - remaining args are pushed to the stack
 - Value is returned in %rax
 - Safe registers: %rbx, %r12..%r15
   - Callee-save
   - A function that uses these registers is responsible for maintaining
     their value from the perspectivie if its caller.
 - Temporary registers: %rax, %rcx, %rdx, %rsi, %rdi, %r8-r11
   - Caller-save
   - A function that uses these registers can expect that any function call
     will clobber them.

### i386 (32-bit)

 - Arguments are passed on the stack.
   - After "enter", args come in as 8(%ebp), 12(%ebp), etc...
   - First one is at 8(...) because:
     - 0(%ebp) is the old %rbp, saved by "enter"
     - 4(%ebp) is the return address, saved by "call"
   - Caller is responsible for moving stack pointer back up, removing
     the pushed arguments.
 - Return value is in %eax
 - Safe registers: %ebx, %esi, %edi 
   - Callee-save 
 - Temporary registers: %eax, %ecx, %edx
   - Caller-save

 
