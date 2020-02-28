
# 5600: How to Optimize an Allocator

## Review: Free List

 - Blocks of free memory are tracked on a singly linked list.
 - Usually in sorted order by memory address.
 - When we free memory we insert into list and coalesce with neighbors.

Two data structures:

 header: { size }
 cell:   { size, next }

Minimum allocation size is 2 words, or 16 bytes on 64-bit.

Efficiency:

 - malloc: O(n)
 - free: O(n)
 
### Doubly Linked List

 header: { size, used }, footer: { size }
 cell: { size, prev, next, used } + footer = 32 bytes

Minimum allocation is 32 bytes.

Efficiency:

 - malloc: O(n)
 - free: O(1)

## New Plan: Buddy System

### Motivation: Trees

Plan A: Balanced Binary Tree ordered by Address

 - node: { size, left, right }
 - malloc: O(n)
 - free: O(log n)

Plan B: Order by Size
 
 - node: { size, left, right }
 - malloc: O(log n)
 - free: O(n)

Plan C: Order by Both

 - node: { size, parent, addr-left, addr-right, size-left, size-right }
   - minimum allocation: 48 bytes
 - malloc: O(log n)
 - free: O(log n)

### Buddy System

 - Start with an aligned chunk of memory.
   - e.g. 1MB aligned at 1MB.
 - Have an array of doubly linked free lists, one for each
   power of two up to chunk size. For 1MB chunk size, that's an
   array of 20 buckets.
 - Cell structure is { size, prev, next, used } = 25 bytes, round up to 32
 - We start with a 1MB block in our biggest bucket, and the rest
   of the buckets empty.
 - To allocate for an empty bucket, split the next biggest bucket, recursively.
   - To allocate 64k, we split 128k, 256k, 512k, 1MB.
   - When we split a block, the pair of blocks are called "buddies".
 - Allocation takes log(chunk size) time. If chunk size is a constant, that's
   O(1).
 - Freeing takes the same amount of time, with the following process:
   - First, we find our buddy. We can do this with pointer arithmetic.
   - If we're size 2^k, the address of our buddy is: (our addr) XOR (1 << k)
   - If buddy is free, we coalesce and recurse.
   - If buddy isn't free, we just mark the block free and put it on the kth free
     list.

Problems with the buddy system:

 - Minimum allocation is still big.
 - Always do a power of two allocation, and power of two requests are
   the worst case.
 - Still feels like it could be faster.
 
Optimizing the buddy system:

 - We can drop the minimum size to 8 bytes.
   - New cell structure is:
   - 1 byte for size (store k, size = 2^k)
   - 1 byte for usedd flag (boolean)
   - 3 bytes for prev ptr (offsets from chunk base)
   - 3 bytes for next ptr
 - That does mean that the max chunk / arena size is 2^24 = 16MB.
 - That's fine, bigger allocations can be mmaped directly. 
 - Alignment is potentially tricky, but that's part of the fun.
 - Powers of 2 are still a problem.

## Buckets

Just like the buddy system, we're going to worth with an array of
free lists, each containing blocks of a fixed size.

Example sizes:

 - 16, 24, 32, 48, 64, 96, 128, 192, 256, 384, 512, 768, 1024, ...
 - [0] [1] [2] [3]

Can't use the buddy system trick of splitting and merging effiently.

Rather than splitting and merging, we'll handle each list separately.

When the user says malloc(100) and the 128 list is empty, we'll mmap
a full chunk (at least one page) of 128's.

 - malloc: O(1) or amortized O(1)
 - free: O(1) ... if we ignore coalescing

Problems:

 - Minimum allocation size is still not great - still have linked list
   and still have 8 byte size field.
 - Power of two sizes are still worst-case.
 - Still have internal fragmentation due to fixed list of sizes.
 - We waste a bunch of memory due to not coalesing.

### Optimizing a Bucket Allocator

Removing the size field:

 - We can put it at the beginning of the chunk.
 - When we allocate, we allocate a memory-aligned chunk filled with
   memory of the same size.
 - To find the beginning, we can round down the memory address to
   the chunk size.

Problem: What about allocations bigger than the chunk size?

 - Make *all* allocations aligned to the same chunk size, with the
   same header.

Problem: How do we handle free lists?

 - Don't have a free list of blocks, have a free list of chunks.
 - Each chunk has a header, but blocks have no overhead.
 - How do we identify which blocks in a chunk are free?
   - Bitmap!
   - For 64k chunks and 128b blocks, this is 512 bits = 64 bytes)

Result:

 - malloc is O(1)
 - free is O(1)
 - min allocation size is 1B
 - power of two sizes are best case, since block overhead is zero 
 - We can coalesce now
   - if a chunk bitmap is entirely marked unused, we can unmap
     that chunk
   - maybe shouldn't do that if there's only one chunk of that
     size allocated

## Next problem: Threads

### Plan A: Per-thread cache

 - One global free list
 - Each thread has a local free list
 - Malloc tries local free list first before taking global lock and
   checking global free list
 - Free usually goes to local free list, but sometimes moves everything
   to global free list (maybe just every 100th call).

Benefit:

 - Actions on local free list have no lock at all.
 
Drawbacks:

 - When we do have to go to the global lock it's still a global bottleneck.
 - Fragmenetation between local free lists

## Plan B: Multiple Arenas

 - Instead of one free list (or other allocator structure), we have an array of
   them.
 - Each thread tries to allocate from a different arena.
 - We'd prefer if each thread sticks to a single arena.
 - Memory is always freed back to its source arena.
 - That means we need a lock for each arena, but the locks probalby
   won't be contested.

Advantages:

 - Tends to avoid bottlenecking on allocation since threads use different
   arenas.
 - No more fragmentatoin than a single arena.

Disadantages:

 - We do need a mutex per arena, and it'll sometimes be contested on free.

### Extending to compliated allocators

 - Multiple arenas works nicely with allocators more complicated
   than a free list.
 - Thread caches can either be thread-local arenas or something
   simpler like a free list per thread.

### Side Node: Thread Local Storage

We can have variables that act like globals that are specific to a single
thread.

Standard solution:

```
  $ man pthread_key_create
```

Easy solution:

 - GCC's __thread keyword.

### Real World Allocators

ptmalloc: The GNU libc allocator

 - Loosely based on the traditional free list design.
 - More recently has added buckets for small allocations.
 - Heavily optimized to not have worst cases.
 - Not really optimized for best-case crazy good performance.

tcmalloc: In the 2000's, Google had too much budget.

 - A bucket allocator
 - Heavily uses per-thread caching
 - Uses a separate garbage collector thread to move stuff from
   local caches to global arena.
   
jemalloc: In the 2010's, Facebook got their turn.

 - Bucket allocator with multiple arenas
 - Uses 2MB chunks
 - Heavily uses memory address tricks to optimize chunk / bucket allocation
 - Most of the optimization is chunk management (e.g. multiple sizes per chunk)
 - Secret sauce: madvise(MADV_DONTNEED)
 














 
