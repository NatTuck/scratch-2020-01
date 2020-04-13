

# CS3650 Spring 2020, Lecture 26: Semester Wrap-Up

What is computer systems? What is this class covering?

 - As an applicaiton programmer, what does a computer
   system give you?

What is a computer system?

 - An operating system
 - An instruction set archetecture

What computer system are we looking at?

 - Linux, specifically Debian 10
 - AMD64


## Assembly Language

 - To access these services, we need to write Assembly
 - The services that the hardware provides: Machine Instruction
 - The services that the OS (kernel) provides: System Calls
   - syscall instruction
   - Which syscalls are defined by the OS

 - Assignments: Assembly Programming

## C Programming

 - HW: Data structures
   - Variable Length array (vector, ArrayList)
   - Hash Table (HashMap)
 - HW: Shell tokenizer

## Processes and Memory

 - A process is a running instance of a program
   - Running a program creates a process
   - Run it twice, get two processes
 - Every process has a virtual address space

Virtual Address Space Layout:

 - Stack, grows down
 - Heap, grows up
 - Text section (from executable on disk; code)
 - Data section (from executable on disk; static data)

API for processes and programs:

 - fork() - Makes a copy of a process, logically including a complete copy of
   the virtual address space.
 - exec() - Load a program from disk into a process, resetting virtual memory
   to the state of a freshly executed program.

## First Challenge: Shell

 - Background: File descriptors

## Shared Memory

One new system call: mmap

 - First example: mapping a file into memory for I/O
 - We can also allocated "shared" memory, which isn't copied on fork.

Once we have shared memory we need to worry about data races.

Conditions for data races:

 - Concurrent execution
 - Shared memory
 - At least one process writes to the shared memory

To avoid data races, we can use locks.

 - Every piece of shared data has an assocated lock.
 - When accessing (read or write) shared data, the accessing process
   must hold (have locked) the lock.

New problem: Deadlocks

 - If we have at least two locks
 - It's then possible to get circular wait
 - And that means deadlocks

Deadlocks can be avoided by restricting how you program.

 - Example: Lock ordering


## Parallel Speedup

 - Assignments: Parallel Sort


## Memory Allocators

Simple solution: Free List

Problems and Solutions:

 - Use (mmap, munmap) system calls to implement (malloc, free) from C standard.
 - First problem: mmap works in minimum 4k pages
   - Solution: Allocate bigger chunks with mmap and then split those up to
     satisfy smaller requests.
   - Unused remaining block is stored in the free list.
   - Linked list is stored directly in the free memory blocks being tracked.
 - Second problem: syscalls are slow
   - Solution: Allocate bigger chunks with mmap and then split those up to
     satisfy smaller requests.
 - Third problem: munmap takes a size, free doesn't
   - Solution: We need to store the size of each allocated block.
   - Example: if the user requests 16 bytes, we find 24 bytes and use the first
     8 to store the size.

 - Assignment: Allocator
 - Challenge: Optimized Allocator

Building a faster allocator:

 - Buddy System
 - "Bucket"

Threads:

 - Multiple Arenas
   - An "arena" is a complete copy of the data structures for an allocator.
   - For a free list allocator, a free list is an arena.
 - Having multiple arenas means that multiple threads can do allocation and
   frees without interfering with each other.

## OS Kernels and xv6

 - xv6 is a real UNIX, v6 UNIX from the late 70's, ported to i386
 - Assignment: Implement an xv6 system call


## Filesystems

 - FAT
   - Old
 - ext ... ext4
   - ext4 is a "modern" journaling filesystem, (NTFS is another example of one)
 - LFS
   - research thing, ended up being useful in SSDs

 - Copy on Write FS's
   - ZFS
   - BTRFS
   - Apple and Microsft have them too now

 - HW10: Build an ext-style FS
 - CH03: Extend it to have basic COW fuctionality




