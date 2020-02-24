
# CS5600

Today: Introducing Memory Allocators

## Next Homework:

 - Write a memory allocator
 - Your allocator should be faster than the two comparable allocators
   for the test programs.
   
## Managing the Heap 

Need to keep track of two kinds of memory blocks:

 - Allocated memory.
   - User has the pointer.
   - We don't actually need to track it ourself, the user will give
     it back to us later with free.
 - Unallocated (free) memory
   - This could be leftover from mmap calls.
   - This could be from a "free" call.
   - We need to track this with a data structure.
   
   
## What is an "arena"?

An arena is the full set of data structures nesissary for a single instance of a
memory allocator. If we're doing a free list, then a free list is an arena.





## Allocator Strategies

Single thread:

 - Simplest: Singly linked free List
 - More complicated (real world, sometimes): Doubly linked freelist
 - Even more complicated: Buddy system (everything O(log n))
 - Real world (super-optimized): Buckets (trying for everything O(1))

Multiple threads:

 - Multiple arenas

Stopped at slide 36




