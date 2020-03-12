
# CS3650: Building a Memory Allocator

What's a memory allocator?

An API with two functions:

 - malloc
 - free

These functions manage the "heap".

More accurate model of the "heap":

 - When a program starts, we probably have 0 bytes allocated for the heap.
 - When the program needs more "heap" memory, it needs to request it from the
   kernel using a syscall.
   - Traditionally used the "sbrk" syscall. The sbrk call is largely obsolete.
   - Memory is allocated now with: mmap(PRIVATE | ANONYMOUS)

```
  // Standard C
  void* malloc(size_t size);
  void free(void* ptr);
  
  // mmap
  void* mmap(size, ...)
  int munmap(ptr, size)
```

Why not just call mmap directly to allocate memory?

 - mmap minimum allocation is 4k, so it's a huge waste of memory for
   smaller requests
 - syscalls are platform specific - we'd like to implement the standard
   C API (malloc / free) so we can have portable programs
 - problem: munmap requires you pass in a size
 - problem: system calls are slow
   - solution: Do less than one mmap call per malloc call.

What does an allocator need to do?

 - On first call to mmap, allocate more space than requested.
   - At least one page.
 - Satisfy subsequent calls from the pool of already-requested memory.
 - Store the size of the allocation with for each allocated block of memory.

Where do we store the size?

 - Option 1: Have a separate data structure storing sizes.
 - Option 2: Store the size with the allocation.
   - This is the easiest. We can store the size before the
     block of memory.

How do we store (info about) free memory?

For each free block of memory we need to store:

 - Address
 - Size

```
    struct mem_block { void* addr; size_t size; }
```

Plan A: An array, wait no, a vector.
Plan B: Unrolled linked list.
Plan C: Use a tree.

 - These plans have a shared problem: They require dynamically
   allocated memory, and we don't have malloc because we're building
   it.

Plan E: Move objects to mainain contiguous free block.


Moivating example:

   a = malloc(50)
   b = malloc(50)
   c = malloc(50)
   free(b)

   free memory is goes through this sequence:
   
    - []
    - [{+0, 4096}]
    - [{+58, 4038}]
    - [{+116, 3980}]
    - [{+174, 3922}]
    - [{+58, 58}, {+174, 3922}]


The trick: The thing we're tracking is *blocks of unused memory*. We can store
stuff in it.

The easiest thing to store is linked list cells.

The data we need to store for each free block becomes:

```
  struct free_list_cell {
     // void* addr;          We're storing this structure at the
                             address, so we need to already know
                             that to get here.
     size_t size;
     free_list_cell* next;
  }
```

```sizeof(free_list_cell)``` = 16

Our minimum allocation size is 16 bytes, or a user request of 8 bytes.
We need to round up the size of smaller allocations.

So we need a constant size static global data structure:

```
   free_list_cell* list_head;
```

## Optimizing a Memory Allocator


### Malloc

 - Given a request for N bytes of space.
 - Add 8 bytes for a size field.
 - For large requests (e.g. >= 4k for the HW):
   - Just call mmap to get a block and return that.
 - Search the free list for a big enough block of memory
   to satisfy the request.
   - Searching a linked list takes O(n)
   - Sort by decreasing size maybe O(1)
   - If we find one either return it or split it and add
     the extra back to the free list.
 - If we don't find an appropriate block, use mmap to
   request a new block.
   - Return the block requested.
   - Add the extra to the free list.

### Free

 - Get a pointer from the user.
 - Back up 8 bytes to find the size field.
 - If it's a big allocation, munmap.
 - Otherwise, insert into free list.
   - If we just cons, then it's O(1)
   - If we sort by memory address, it's O(n)
 - If there are adjacent free blocks already on the list, coalesce.
   - With unsorted list, coalesce is O(n^2)
   - Either O(n) or it already happened as part of the insert.

So both malloc and free are O(n) with a naive free list.

Linked list data structure:

```
// Min allocaiton = 16 B
struct node {
    size_t size;
    node* next;
};
```


What's faster than a linked list? A tree (balanced binary search tree).

```
```
// Min allocation = 24 B
struct node {
    size_t size;
    node* left;
    node* right;
};

```

Order by memory address:

 - malloc - O(n)
 - free - O(log n)

Order by size:

 - malloc - O(log n)
 - free - O(n)


```
// Min allocation = 40 B
struct double-tree-node {
    size_t size;
    node* size_left;
    node* size_right;
    node* addr_left;
    node* addr_right;
};

```

Order by both:

 - malloc - O(log n)
 - free - O(log n)


Getting even more efficient: Restrict allocations to specific sizes.

## The Buddy System

Start with an array of free lists.

Each free list is doubly linked, to allow O(1) insert or delete.

```
struct buddy_node {
    size_t size;
    bool used;
    
    buddy_node* next;
    buddy_node* prev;
};

struct buddy_header {
    size_t size;
    bool used;
};

```

Each free list contains blocks of some fixed, power of 2 size.

Let's assume our total heap size is 64k.

We'll have an array of 17 free lists:

 [16] -> list of free blocks of size 64k
 [15] -> list of " of size 32k
 [14] -> " 16k
 ...
 [5]  -> " 32

We'll start by allocating one free block of size 64k, and it'll be aligned to
a memory address divisible by 64k.

Heap:

 [16] -> [+0]
 [15] -> 
 [14] -> 
 ...

+0 <- malloc(16k)



free(+0)






