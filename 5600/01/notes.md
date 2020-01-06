
# CS5600: Computer Systems
# Section 1
# Instructor: Nat Tuck


##


 - To do anything, a program needs to use hardware resources.
 - Old computers ran one program at once.
 - Once you have two or more programs on one computer, you get conflicts.
 
 - Add a program: The OS kernel, to manage shared resources.
 - Only the kernel can access hardware directly.
 - Other programs need to ask the kernel for help.
 - "Normal" instructions don't need this help.
 - To access shared resources, you do a system call.

Instruction set archetectures:

 - Common: Deravations of intel x86 (32-bit) (derived from the 
   16-bit the Intel 8086).
   - Actually, 64-bit AMD64.
 - More common: ARM, that comes in 32 and 64-bit variants.
 - Now uncommon: SPARC, from Sun, now Toshiba
 - Fancy in theory: RISC-V
 - Others: MIPS, PPC

A concrete computer system:

 - Instruction Set Archetecture: AMD64 
   - We'll do some x86 as well. 
 - Operating System: Linux (Debian 10)

## Course Web Page

 http://khoury.neu.edu/~ntuck

## Logging in to Inkfish

 - Khoury College Account
 - http://my.ccs.neu.edu/ 



## Intel ISA History

1978: 8086 Microprocessor - 16 bit

 - It had 16-bit machine words, so 16-bit registers
 - It had a 16 bit bus connecting to memory.
 - Maxes out at 64kB of physical memory.
 - 9 registers
   - ax, cx, dx, bx, si, di  ||  bp, sp 
   - special purpose: ip

late 80's: 80386 - 32 bit microprocessor, backwards compatible

 - 32-bit registers and machine words
 - 32-bit bus connecting to memory 
 - had the same old registers, still storing 16-bit values
 - new names:
   - eax, ecx, edx, ebx, esi, edi, ebp, esp
   - eip

2004: AMD Athlon 64 ~2003
 
 - 64-bit registers and machine words
 - 64-bit bus connecting to memory 
 - had the same old registers, still storing 16-bit and 32-bit values
 - new names:
   - rax, rcx, rdx, rbx, rsi, rdi, rbp, rsp
   - rip
 - new registers:
   - r9...15

