
# CS3650: Memory Allocator

A memory allocator provides two functions:

```
void* malloc(size_t size);
void free(void* ptr);
```

These functions implement the "heap".

Historically:

 * The heap is one region of memory, that is allocated when the
   program starts.
 * The sbrk system call is used to grow the heap.

On a modern system:

 * A newly started program has no heap allocated.
 * Memory is allocated with: mmap(PRIVATE | ANONYMOUS)

```
// C standard memory allocation API
void* malloc(size_t size);
void free(void* ptr);

// POSIX memory allocation syscalls
void* mmap(..., size, ...);
int munmap(ptr, size);
```

Simple plan:

 * malloc just calls mmap
 * free just calls munmap

Problems:

 * Free doesn't take a size, munmap does, so we need to store the
   size somewhere.
 * Minimum allocation size for mmap is one page. That's horribly inefficient for
   small allocations.
 * System calls are slow. The overhead is constant, reguardless of size of
   memory allocated. We want to do as few system calls as possible.
 * We'd like to reuse memory rather than immediatley returning it to the OS.

So we're going to call mmap as infrequently as possible, and when we do call
mmap we're going to request extra memory. We'll store the extra memory for
future requests, and keep around free memory for reuse.

We also need to track size. Where?

Plan A: Have an external data structure (e.g. hash map) that stores metadata
about blocks of memory.
 - This isn't nessisarily wrong; there's some tricks that can make this work.
Plan B: Store the metadata with the block of memory.
 - This is easier, we'll go with this plan for now.

Two kinds of blocks of memory:

 - Allocated blocks of memory: The user has a pointer to these, they'll give it
   to us when they call free, we don't need to track it.
 - Free blocks of memory: We need to track these.
   - Leftover pieces of bigger blocks.
   - Freed blocks.

Freed blocks example:

 a = malloc(16)
 b = malloc(16)
 c = malloc(16)
 free(b)
 
Free blocks: [{+24, 24}, {+72, 4024}] 

 a = +8
 // b = +32  // freed
 c = +56

For each free block, we need to track:

```
struct free_block {
    void* addr;
    size_t size;
};
```

Where do we put our collection of free blocks?


Plan A to store a sequence: A vector, but we're building malloc.



Remember: We're the memory allocator, and the thing we're trying to
track is free (unused) blocks of memory. We can put whatever we
want in there: like linked list cells.

```
// The address of the memory we're tracking is the address
// of the struct.
struct free_block {
    size_t size;
    free_block* next;
};
```

We still need a pointer for the head of the list. We can just use a global; it's
fixed size.

```
   free_block* free_list_head;
```


What happens if I do: a = malloc(4); free(a);

problem: This isn't enough space for a free_block.
solution: Always allocate at least enough space for our free\_block;
  our minimum request size is 8, minimum alloc size is 16.

## Optimizing a Memory Allocator

### malloc

 - User calls function, requesting a pointer to N bytes.
 - We add 8 to N to make space for the size field.
 - If this is >= 4096 bytes, just call mmap.
 - Scan the free list for an appropriate block.
   - O(N) to scan the whole list
   - O(1) if list is sorted by size decreasing
   - Split it, return extra to free list.
 - If nothing on free list, call mmap
   - Split it, return extra to free list.
 - When we return a pointer, return the pointer to
   after the size field.

### free

 - User calls free with the pointer we gave them.
 - Subtract 8 bytes to get pointer to size field.
 - Declare that to be a free list cell struct.
 - If size >= 4096, just call munmap.
 - Otherwise, insert into free list.
   - O(1) to cons onto head of list.
   - O(N) if list is sorted by size.
   - O(N) if list is sorted by address
 - Make sure adjacent blocks get coalesced together
   into one big block.
   - O(n^2) for completely jumbled list.
   - If sorted by address, this is free or O(N).

Result: Both malloc and free are O(N).


### Optimizing


 - To get better algorithms, we need a better data structure.




```
// The address of the memory we're tracking is the address
// of the struct.

// Balanced binary tree.
// sizeof(node) = 24 = minimum allocation
struct node {
    size_t size;
    node* left;
    node* right;
};
```

Tree is sorted by size:

 - malloc is O(log n)
 - free is O(n)

Tree is sorted by address:

 - malloc is O(n)
 - free is O(log n)



```
// The address of the memory we're tracking is the address
// of the struct.

// Two balanced binary trees.
// sizeof(node) = 56 = minimum allocation
struct node {
    size_t size;
    node* addr_left;
    node* addr_right;
    node* size_left;
    node* size_right;
    node* addr_par;
    node* size_par;
};
```

Two trees sorted by both:

 - malloc is O(log n)
 - free is O(log n)

### Optimization of trees: The Buddy Allocator

Idea: What if we constrain what sizes we allocate?

We'll always allocate powers of two.

Let's start with a heap that's 64k.

We have an array of freelists, one for each power of two
up to that heap size.

```
free_cell* free_lists[17];
```

Our free_cell structure is going to be a doubly linked list, to allow O(1)
insert and delete.

```
// Free blocks, minimum size = 32
struct node {
    size_t size;
    bool   used;
    node*  next;
    node*  prev;
};

// Every allocated block:
struct allocated_header {
    size_t size;
    bool   used;
};
```

Start up by allocating a single block of size 64k, with a memory address aligned
at 64k.

```
fl[16] = [{+0, 64k}]     // 64k
fl[15] = []              // 32k
fl[14] = []              // 16k
...
fl[5]  =                 // 32B
// five slots wasted
```

{+0, 16k} = malloc(16)
free({+0, 16k})
