
# CS5600: Allocators, pt3

Collatz Conjecture

Consider this procedure: Start with any positive integer x. If it's even, take
x/2. If it's odd, take 3*x+1. Repeat until we get into a loop.


5 -> 16 -> 8 -> 4 -> 2 -> 1
                          1 -> 4 -> 2 -> 1
                          
The conjecture is that every possible positive integer will end up
in this loop.

The test cases solve the problem of how many steps to get to one, inefficiently.
 
 - First, build a collection of the whole sequence for that input.
 - Then take the sequence length.


## Optimizing the Allocator

First thing:

 - Write a simple allocator that you can understand.

Compared to the xv6 allocator or a functionally similar rewrite of it, you have
two basic problems:

You want a better algorithm / data structure for the allocator.

 - ex. buddy system, buckets, etc

You need to avoid lock contention.

 - Two basic strategies: Multiple arenas, Per-thread caches
 - Definitely worth looking into: thread local storage (e.g. gnu __thread
   extension)

Here's a trick: Your performance only matters on the two concrete test
programs.

 - You need to be able to *run* arbitrary programs.
 - But you only need to be fast on those two.

Example: Instrument the programs and ask "What is the distribution of memory
allocation sizes?"

Imagine we tested it and found out that both programs have 90% allocations
of size 250 and 300.

In that case, a good design might be:

 - Singly-linked boring global free list.
 - Special case handling for allocations of size 200-300, using single
   bucket for size-300 allocations.
 - Can have thread-local caches of the size-300 bucket.
 - To handle coalesing:
   - We could add a "used" header to all allocaotions.
   - Always allocate size-300 objects as a full page-aligned page (13 blocks).
   - When we free a block, we check all the blocks on its page. If they're all
     free, coalesce them and throw the page on the normal free list.




