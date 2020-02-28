
# CS3650: Virtual Memory and Cache

Upcoming assignment: Memory allocator

You'll be implementing malloc and free.

Memory allocator slides are linked in today's notes.

## Page Tables

 - Each process gets its own virtual address space.
 - Pages are 4k chunks of memory, and are the unit of memory management.
 - This means that each process needs its own page table to translate
   virtual addresses to physical addresses.

32-bit page tables (for i386)

 - How many potential 4k pages in a 32 bit address space?
   - Each page is 2^12, that leaves 20 bits for page number.
   - So we can have 2^20 pages = 1M

Simple page tables:

 - We need to map (virtual page #) to a PTE, 
   which is (physical page number, flags)
 - Flags are stuff like valid?, present?, r/w/x? 
 - PTEs on 32-bit x86 are 32 bits
 - Easiest way to map an integer to some data is an array
 - The page table for each process is 4 MB
 - This probably isn't how page tables really work.

Optimizing page tables:

 - Plan A: Hash map
   - Solves the space problem.
   - Hash map operations are amortized constant time
   - That means it's sometime linear
   - You can built a realtime hash table
   - Page tables need to be pretty simple, since we're going to implement
     them in hardware and don't want bugs.
 - Plan B: Binary Search Tree
   - Operations are all log(N)
   - Actually, we know log(N) = 20, so O(20) = O(1)
   - But 20's kind of a big constant
   - This doesn't help with the complexity thing

How it actually works: Multi-level tables

 - Technically, this is a kind of fixed-depth Trie.
 - It's two levels of arrays.
 - The 20 bit page number is split into two parts:
   - 10 bits: Index into page directory array.
   - 10 bits: Index into 2nd-level page table array.
 - Page directory maps index -> address of 2nd level table.
   - Has a valid? bit, if there's no addresses with that
     prefix there's no 2nd levle table.
 - There are up to 1024 2nd level directories, mapping 2nd
   10 bits to a PTE.

Example: A process with four pages: stack, heap, text, data

 - With single level table, this takes 4 MB.
 - With two-level table. 4k for page directory + 4k for at least one
   2nd level table, up to 16k for 4 2nd level tables
   - total is 8 - 20kB

## 64-bit amd64 machines

 - Memory addresses are 64 bits
   - Address space size: 16 EB (quintillion)
 - Wait, no, addresses are really 48 bits stored in a 64 bit integer
   - Address space size: 256 TB
 - Problem: Intel's shipped machines with more than 256 TB of "RAM".

With 48 bit address and 4k pages:

 - 12 bits is page offset
 - 36 bit page number
 - PTEs are 64-bits
 - Single level page table would be: 2^36 * 8 bytes = 2^39 = 512 G

How do multi-level page tables work?

 - 48 bits total
 - 12 bits for page offset
 - 36 bit page number
   - One option: 3 levels, 12 bits each
   - Each table has 4096 entries * 8 bytes = 32k
   - What AMD did: 4 levels, 9 bits each
   - Each table has 512 enties * 8 bytes = 4k

## Problem: Virtual addresses sound slow.

On 64 bits, every memory access involves an extra four
memory accesses. That's a 5x speed penalty.

Clearly, this doesn't actually happen.

Solution: Caching in the processor

 - Each processor core has a Translation Lookaside Buffer (TLB)
 - This caches virtual -> physical page mappings
 - Modern processors tend to have 1536 entries

## An Example

```
int* xs = // two pages of stuff;
int sum = 0;
for (int ii = 0; ii < 2048; ++ii) {
    sum += xs[ii];
}
```

How many memory loads with single level page table?

 2048 * 5 = 10k


How about with a four-level table?

 2048 + 4 + 4 = 2056

 Virtual memory overhead is 8 / 2048 = 0.4%

## Context Switches

Single core processor running two processes that each have one
thread.

 - Process 1 is running.
 - Process 2 is ready to run.

Process 1 calls sleep(1).

 - Process 1 saves callee-save registers and then does syscall
 - In the syscall handler, we save off the rest of the process state
   - To the process stack
   - To the kernel "thread" / "process" struct.
   - This includes the CR3 register, which points to the page table.
 - The kernel scheduler will decide to run process 2.
 - Kernel restores process state before calling sysret.
   - The CR3 register.
   - Other stuff from the thread/proc structs.
   - Stuff from the process 2 thread's call stack.

Other things that trigger a context switch:

 - Interrupts
 - This includes the timer interrupt

Context switches between threads are the same, except CR3 doesn't change. When
CR3 changes, we need to invalidate the TLB.

This is one of the reasons why threads can be faster than processes.


## Predicting Performance

### Arithmetic

Intel(R) Core(TM) i7-8650U CPU @ 1.90GHz

Expected turbo speed: 4 GHz

Addition: We can do an addition in one clock cycle.

```
for (;;) { a += 5; }
```

Complication: There are 4 ALUs, each can do one integer
arithmetic operation each cycle as long as there are no
dependencies.

```
// 4 iterations per nanosecond
for (;;) { a += 5; b += 5; c += 5; d += 5; }

// 2 iteratoins per nanosecond
for (;;) { a += 5; a += 5; c += 5; d += 5; }
```

Memory:

L1d cache:           32K
 - Latency: 1ns = 4 clocks
 - Throughput: 1000 GB/s
L1i cache:           32K
L2 cache:            256K
 - Latency: 3ns = 12 cycles
 - ...
L3 cache:            8192K
 - Latency: 11ns = 44 cycles
 - ... 
System Memory:       16G
 - Latency: 60ns = 240 clocks
 - Throughput: 20 GB/s

Cache operates in cache lines (64 bytes)
 
 - 1B / (16 ints per cache line) = 60M
 - 60M * 60ns = 3.6 seconds

Estimates:

 - Just the adds: 1/8th of a second
 - All the arithmetic: 1/8th of a second
 - Memory throughput: 1/3rd of a second
 - Cache misses: 3.6 seconds
































