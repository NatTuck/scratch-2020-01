
# CS5600: Lecture 2

Course site: http://khoury.neu.edu/home/ntuck

Last time:

 * Course overview, syllabus
 * One assembly example.

Today:

 * amd64 and i386 assembly intro

# History of Intel ISA

## Conceptual 8-bit archetecture

 - 8 bit memory addresses means max 256 bytes of RAM
 - registers: a, b, c, d, ip

## 8086 16-bit microprocessor

 - 16-bit memory address, bus size, word size
   - 64k RAM
 - new names: ax, bx, cx, dx
 - new registers: si, di, sp, bp
 - can access lower 8 bits of a register: al, bl, cl, dl
 - name of ip didn't change

IBM PC:

 - Could support 640k
 - Address space size was 1MB
   - 20 bit physical addresses 

# i386 32-bit extension

 - 32-bit memory addresses, bus size, word size
 - max physical memory: 4GB
 - new names for registers: eax, ebx, ecx, edx, esi, edi, esp, ebp; eip

# amd64 64-bit extension

 - 64-bit memory addresses, word size
   - 48 bit physical bus
   - 64 bits would be: 16 EB, 16 million TB 
   - 48 bit is: 256 TB
 - new names for registers: rax, rbx, rcx, rdx, ...
 - new registers: r8..15


## Different assembly languages

Differences between 32 and 64-bit asm:

 * AMD64 has more (and bigger) registers.
 * Different calling conventions.
   * 64 bit args go in: %rdi, %rsi, %rdx, %rcx, %r8, %r9, then the stack
   * 32 bit args go all on the stack (in reverse order)
   * In both cases returns happen in the *ax register.
   
Another complication: Two different syntaxes

 * AT&T syntax, standard with GNU software (Linux + GCC)
 * Intel syntax - this is what we see in the documentation
 
Differences:

 * AT&T has % and $ characters. AT&T puts the result register last.
 * Intel syntax doesn't have "%" or \$, and it puts the result 
   register first.
 * The expressoins for calculating memory addresses look different.

## Places to put stuff

Where can we put stuff in assembly?

 - #1 option is registers
   - fast, easy
   - registers aren't memory, eg. they don't have addresses
 - #2 option is in memory

 - In C we have local variables
 - In assembly we don't, but we'd like to pretend

Register conventions:

 - Temporary registers: %rax, %rcx, %rdx, %rsi, %rdi, %r8..r11
   - If you call a function, you assume that it overwrites these registers.
   - If you want to keep it, you need to do "caller save", and save the
     value somewhere else before calling the function.
 - Safe registers: The other ones (%rbx, %r12..15, stack stuff)
   - If you call a function, you can assume that it won't overwrite
     the values in these registers.
   - If you want to use one of these registers, you need to do "caller save",
     saving the values at the start of your function and restoring them
     before returning.

Other place for function-call specific data is the stack.










