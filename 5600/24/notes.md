
# CS5600 Spring 2020, Lecture 24: Wrap Up

## What is computer systems?

 - Kernel-space programming
 - User-space programming
 - Systems programming is at the line between the two.
   - That means we're dealing with system calls.
   - Scenario A: We're writing a userspace program that makes syscalls.
   - Scenario B: We're writing kernel code that implements a syscall.

Concrete platform:

 - Linux operating system, specifically Debian 10.
 - AMD64
 
Secondary platform: xv6 on i386

## Software/Hardware Interface

 - Most obvious: Instruction Set
 - To see that we wrote AMD64 and i386 assembly

 - The other part of the hardware / software interface we care about
   is interrupts, but that comes up later.

## System Calls

Calling from assembly:

 - On AMD64, this is the "syscall" assembly instruction.
 - On i386, this is a software interrupt.   Linux int 0x80, xv6 int 64 ?
 
Flow once we get to the kernel:

 - (i386) Interrupt number is looked up in interrupt vector
   - That's a function pointer, we call it, it does:
 - Syscall number is looked up in the syscall vector
   - That's a function pointer
   - That function is called to handle the syscall

## xv6

 - Teaching OS
 - Design goal: Also be a real OS
 - To be both, a real historical OS was used (v6 UNIX, ported to i386)

Stuff we covered about kernels:

 - Boot sequence
 - Syscall sequence
 - xv6 hw: Implemented a syscall
 - xv6 hw: Added a shell feature
 
## Processes and Memory

 - A process is what you get when you a program
   - Each running instance of a program is a process
 - Each process has its own virtual address space

Virtual address space layout:

 - Stack, grows down
 - Heap, grows up
 - Data section from executable
 - Text section from executable (code)

Each process has this stuff, and one process can't mess with the memory of
another process, since a virtual address can't reference another processes's
private memory

Creating processes:

 - fork() - Copy a process, including (logically) all of its virtual address
   space.
 - exec() - Load a program from disk into the current process, replacing what's
   there and giving a clean address space.

## Concurrency and Parallelism

 - mmap
   - Can map files from disk into memory for I/O.
   - Can also allocate shared memory, which won't be CoW on fork().

 - Assignment: xv6 shared memory
   - Wrote a userspace mutex (spin lock)

Shared memory is a problem.


Data races:

 - If we have shared memory
 - And concurrent execution
 - At least one process writes

We can avoid data races with locks
 
 - Each piece of shared data has an associated lock
 - All accesses to shared memory are done only when
   holding (you have locked) the lock.

Locks create a new problem.

 - If you have more than one lock, you can deadlock.
 - Requirement: Circular wait

We can avoid deadlocks with programming restrictions

 - For example: Lock ordering

## Parallel Speedup

 - Assignment: Parallel Sort with Processes and Threads


## Memory Allocators

Simple design: Free list

Problems and solutions:

 - We need to adapt the memory allocation mechansim provided by the kernel,
   the mmap syscall, into the C api (malloc, free).
 - Problem 1: minimum mmap size is 4k
   - Need to split them up for smaller allocations
 - Problem 2: syscalls are expensive
   - Need to reduce the count by doing larger requests and then
     splitting them up
 - Problem 3: munmap takes size and free does not
   - Need to store size for each allocation
   - Simple plan: Store header *before* allocation
     - So malloc(16), we actually allocate 24, with 8 for size field.

More complex designs:

 - Buddy System
 - "Bucket"

Another problem: Threads

 - Multiple arenas
   - An "arena" is a complete copy of the data structures for a memory
     allocator, so that threads can do memory allocation ops independently
     without conflict.

 - Assignment: Optimized memory allocator

Garbage Collector

 - Mark and sweep
   - Mark: Scan the whole live heap, starting from roots (e.g. the stack)
     and mark each live object.
   - Sweep: Scan every object on the heap, and if it's not marked free it.

 - Assignment: GC

## Filesystems

 - FAT
   - An old design
 - ext ... ext4
   - "modern" journaling filesystems, including stuff like NTFS
 - LFS
   - Experimental
   - Exactly what was needed for SSD controllers

 - Copy on Write filesystems
   - ZFS -> BTFS -> Apple / Microsft

 - Final Assignment: Complete ext-style filesystem with basic COW features

