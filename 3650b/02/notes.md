
# CS3650: Systems

If you missed it: http://khoury.neu.edu/home/ntuck



# History of Intel family ISA

## Imaginary 8-bit processor

 - 8-bit processor
 - 8-bit word size, data bus, memory address
 - 8 bit addresses mean maximum: 2^8 = 256 bytes of RAM
 - 4 genreal purpose registers: a, b, c, d
 - 1 special register: ip

## Intel 8086

 - 1978
 - 16-bit processor so,
   - 16-bit word size
   - 16-bit data bus
   - 16-bit memory addresses
   - max RAM: 2^16 bytes = 64K 
 - new names for extended registers: ax, bx, cx, dx
   - can still talk about lower 8 bits using names: al, bl, cl, dl
 - new registers: si, di, sp, bp
 - at least one special purpose register: ip

## i386 (late 80's)

 - 32-bit extension of the 8086
 - 32-bit words, data bus, memory addresses
   - max RAM: 2^32 = 4 GB
 - new names for regisers: %eax, %ebx, %ecx, ..., %edi, ..., %esp, ...
 - old names still worked for pieces of the register: %ax, %al

## AMD64 (~2002)

 - also called: x64, x86_64, Intel64
 - 64-bit extensoin of i386
 - 64-bit words, memory addresses
 - 48-bit hardware data bus
   - max RAM for a 64-bit address: 16 EB
   - max RAM for a 48-bit bus: 256 TB
   - some intel servers now use a 57-bit bus
 - new register names: %rax, %rbx, ..., %rdi
   - old names still work for a part of the register
 - new registers: %r8..%r15






