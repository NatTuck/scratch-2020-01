
# CS5600: Virtual Memory / Page Tables

Every memory access involves a lookup in the page
table, to translate a virtual address to a physical address.

This mapping has granularity of 4k pages.

If we have a 32-bit memory address:

 - 20 bits for page index
 - 12 bits is offset within a page

These two addresses refer to the same page:

 - 0x55553300
 - 0x5555330A

If the page table were a single array, how many slots would it have (on 32-bit)?

 - 2^20 = 1-megapage ~= a million
 - Each page table entry might be 64 bits 
   - Physical memory prefix is 20 bits
   - random stuff and flags might be 44 bits
   - This table is 8 MB, per process
   - There must be some optimizaitons to make this work.
 - Other stuff in the page table:
   - Valid? bit
   - Permissions bits (e.g. r, w, x)
   - In memory? bit
     - If set, access physical memory
     - If not set, hardware segfaults, and kernel needs to go
       find the data.
     - For example, the kernel may have another table that indicates
       that this data is actually in a file.
     - In fact, *all* data with a memory address on a Linux-style system
       has a home somewhere on a disk.
       - Either data comes from a file on disk
       - Or, for "anonymous" data, it's backed by swap space.
   - Copy on write? bit 



Slides: Ended at slide #53


