
# CS5600: More on GC

## First thing: Online Teaching

 - No in-person lectures.
 - There will be video lectures or streaming lectures.
 - No in-person office hours.
 - Instead, we'll try Microsoft Teams.

Assignments stay exactly the same.


## Second thing: HW08 Questions




## Simplest bucket allocator

 - Array of singly linked free lists.
 - Each list contains blocks of one size.
 - The lists are handled separately - when a list is empty and we need a block
   of that size, we mmap a new page or chunk of multiple pages.
 - Advantage of this strategy: Coalescing is simple - either you don't do it, or
   you only do it when an entire chunk is on the free list.

Bitmap optimization for coalescing whole pages.

 - We have a free list for size = 128 blocks.
 - When the free list is empty, we allocate the following chunk:
   - One 4096B page.
   - That would be 32 blocks of size 128.
   - We reserve the first block for metadata.
   - The metadata is a bitmap of 128 "used" flags.
   - That takes 128 / 8 = 16 bytes.
   - On free, we use pointer arithmetic to find the 0th block on the page and
     then check if the bitmap is all 0's. If so we can unmap.

Implementing realloc:

```
void* realloc(void* addr1, size_t size2):
    // TODO: How to handle mutex?

    void* addr2 = malloc(size2);
    size_t size1 = get_size(addr1);
    memcpy(addr2, addr1, size1)
    free(addr1);
    return addr2;
```












