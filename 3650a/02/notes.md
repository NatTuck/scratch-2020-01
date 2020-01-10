

In case you missed it: http://khoury.neu.edu/home/ntuck



# History of the Intel family ISAs

## A possible 8-bit Intel processor

 - This is an 8 bit processor.
   - 8 bit memory bus
   - 8 bit word size (= size of register)
   - 8 bit memory addresses
     - 2^8 = 256 bytes maximum memory
 - 4 general purpose registers: %a, %b, %c, %d
 - one special purpose register: ip

## The 8086 - a 16 bit processor.

 - This is a 16-bit processor.
   - 16 bit memory bus
   - 16 bit word size
   - 16 memory address size
     - max memory? 2^16 = 64K
 - new names for 16-bit extended registers: %ax, %bx, %cx, %dx
   - can still access the register as an 8 bit value using
     alternate names: %al, %bl, ...
 - new registers: %si, %di, %sp, %bp

## The i386, a 32-bit processor

 - This is a 32-bit processor
   - 32 bit bus, word, address
   - Max memory: 2^32 = 4GB
 - new names for the 32-bit extended registers: %eax, %ebx, ..., %edi, ... 
   - %ax is still the low 16 bits
   - %al is still the low 8 bits

## amd64 - a 64-bit extension

 - also known as: x64, x86_64, Intel64
 - This is a 64-bit processor
   - 64-bit word, 64-bit memory address
   - 48-bit hardware data bus
   - 2^64 = 16 EB
   - 2^48 = 256 TB
   - 2^57 = ???
 - New names for the 64-bit extended registers: %rax, %rbx, ..., %rdi
 - New registers: %r8..%r15
   - %eax, %ax, %al are still there, the lower half, quarter, and 8th of
     of the %rax register




