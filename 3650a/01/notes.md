
# CS3650: Computer Systems

Section 02
Instructor: Nat Tuck


# Historical Computers

 - One program running at a time.

Run multiple programs? Problem: Allocating shared resources

Solution: Add another program, the OS kernel

Programs have two ways to interact with the computer:

 - Run machine instructions
 - System calls

System calls and machine instructions are different on different computers.


Two things to pick: An Instruction Set Archetecture, an Operating System

ISAs:

 - x86, Intel's 32-bit instruction set archetecture
   - This is what personal computers have "always" run. 
   - Now we use amd64, the 64-bit extension 
 - ARM, the archetecture family from Acorn Risc Machines
   - Currently on v7 or v8
   - Both 32 and 64 bit variants

Weirder ones:

 - MIPS
 - IBM Power, (the PS3 had Cell coprocessors too)

Operating System: Linux

Our computer system: Linux on AMD64 (Debian 10)


http://khoury.neu.edu/~ntuck



http://my.khoury.neu.edu


# History of Intel ISA

1978: Intel released the 8086 microprocessor.

 * This processor was a 16-bit processor.
   * It had a 16-bit bus connecting to memory.
   * That means 16-bit memory addresses.
   * A memory address is (in this case and usually) a place to
     keep 1 byte of data.
   * So the maximum amount of memory is 2^16 bytes.
   * 2^16 = 64k
   * Registers were 16-bit








