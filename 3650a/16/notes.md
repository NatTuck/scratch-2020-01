
# CS3650: Virtual Memory and Caches

Next assignment will be a memory allocator.

You get to implement malloc and free.


## Today: Page Tables

 * Every process has its own virtual address space
 * Memory, both physical and virtual, is managed in 4k pages
 * Each process has a page table, mapping virtual page #'s to physical page #'s

32-bit page tables:

 * A memory address is 32 bits
 * How many potential 4k pages are there in a 32-bit address space?
   * 2^20 = 1M 
   * 4k = 2^12 - low 12 bits is page offset, that leaves 20 bits for page #
 * Each page table entry on an i386 32 bit system is 32 bits.
   * Index into the page table is the virtual page number.
   * The table is effectively a map from (virt page #) -> (page table entry)
   * A page table entry has:
     - A physical page # (20 bits)
     - A bunch of flags (12 bits), e.g. present, readable, writable, executable
   * Problem: How big is the page table if it's one array?
     - 4 bytes per entry * 1M entries = 4M
     - i386 machines had around 4MB of RAM, so that'd be 100% of memory
       for each process. Clearly this isn't actually how this works.

Other plans:

 - Hash tables:
   - Operations take amortied constant time.
   - Sometimes operations take O(n) - which isn't OK for
     memory accesses.
   - Page table structure wants to be pretty simple. It's implemented
     in hardware, so we'd like to be pretty sure there are no bugs.
 - Balanced Binary Search Tree
   - Operations take log time.
   - This fails the complexity requirement pretty hard.

Multi-level page tables:
 
 - To be overly technical, this is a kind of Trie 
 - Instead of one array, we have two levels of arrays. 
 - Split the address into three parts:
   - 10 bits: Page directory index
     - Maps directory index -> 2nd level index
     - Includes a valid? flag.
   - 10 bits: 2nd-level table index
     - There are potentially 1024 of these, one for
       each row in the page directory.
     - Maps second 10 bits of address to PTE.
   - 12 bits: Page offset

Imagine we have a process with 4 pages mapped: stack, heap, data, text

 - With a single-level page table, the table takes 4MB.
 - With multi-level tables:
   - Page directory takes 4k.
   - Each second level table takes 4k, we have 1-4 of them.
   - So between 8k and 20k.

64-bit systems:

 - On amd64, a page table entry is 64 bits
 - First gen AMD64 processors 48-bit virtual address space.
   - What's 2^64?    16 Quintillion bytes = 16 EB.
   - What's 2^48?    256 TB
 - Problem: Intel's now selling servers with more than 256 TB of "RAM". 
 - How many 4k pages in a 48-bit address space?  64G = 2^36
   - 2^36 * 8 = 2^39 = 512G of page tables per process
 - Multi-level page tables on 64-bit:
   - Plan A: 4 levels at 9 bits each
     - This is what AMD did
     - Because this means that each table is still 4k.
   - Plan B: 2 levels at 18 bits each
   - Plan C: 3 levels at 12 bits each
 - Four tables makes lookups take longer.

On Intel's big servers, they need to support more than 256 TB of RAM.

 - What did they change to make this work?
 - Add a level, for 5 of them.
 - 5 * 9 + 12 = 57

## Problem: Every memory access requires an address translation

 * If we have four level page tables, that means every one access
   we mean to do really takes 5 accesses:
   - Four for the page tables.
   - One to do work.
 * This is solved with a cache.
   - Called the Translation Lookaside Buffer (TLB).
   - In hardware, in each core, usually has 1536 entries.

## Example: Accessing an array:

```
int* xs = ... // starts at a page boundary
int sum = 0;
for (int ii = 0; ii < 2048; ++ii) {
    sum += xs[ii];
}
```

# Context Switches

 - Separate processes have separate virtual address spaces.
 
How do we switch from one process to another?

 - In calling a system call like sleep, the old thread in the old 
   process saves its current state.
   - To its stack.
   - Syscall instruction triggers handler which registers to stack.
   - After the syscall operation, to the process/thread struct in the kernel.
   - That includes the CR3 register, which points to the page table.
 - The kernel restores the saved state of the new process / thread to
   be scheduled.
   - Restoring its CR3 switches virtual address spaces.
   - Before sysret instruction, we restore registers from stack.

Switching between threads is the same, but CR3 stays the same.

When we change CR3 we also need to invalidate the TLB.

Reasons for context switches:

 - System calls
   - Especially when they block (e.g. I/O, sleep, mutex_lock)
 - Interrupts
   - Especially the timer interrupt

## Test computer

 - Thinkpad X1 Yoga G3 with Intel Core i7-8650U.
 - Clock speed = 4 GHz
 - 16 GB of RAM (DDR3 2133)
   - Latency: 60ns = 240 clocks
   - Throughput: 20 GB/s
 - L1d cache:           32K
   - Latency: 1ns = 4 clocks
   - Throughput: huge
 - L1i cache:           32K
 - L2 cache:            256K
   - Latency: 3ns = 12 clocks
 - L3 cache:            8192K
   - Latency: 11ns = 44 clocks


Each core can do an add every cycle.

```
for (;;) { a += 5; }
```

So that's 4 billion adds / second.

To complicate things further, each core has four ALUs, that can *each*
execute an add per cycle if they don't depend on each other.

```
for (;;) { a += 5; b += 5; c += 5; d += 5; }
```

So that's 16 billion adds / second.

Latency to memory is 60ns. Cache loads data in 64 byte cache lines.

Load 1B integers / (16 ints per cache line) = 64M

Predicitons for our program: 

 - Arithmetic operations: 1/8th of a second.
 - Raw memory throughput: 1/3rd of a second.
 - Cache misses: 64M * 60ns = 3.84 seconds

One more part to the story: The prefetcher

 - Hardware, in the cache
 - Tries to guess memory access and request
   stuff early.
 




