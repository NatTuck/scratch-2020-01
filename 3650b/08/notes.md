
# CS3650

Today's topic: Hash Tables


## Key-value Map Data Structure

### Plan A: Association List (or alist)

 - A linked list of (key, value) pairs.
 - Problem: Operations are O(n)
 - Problem: Linked lists have space overhead.
 - Does see some use in practice.

### Plan B: A Balanced Tree

 - Balanced binary search tree like a Red-Black tree.
 - Advantage: Operations are O(log n).
 - Problem: Trees have some space overhead.
 - Problem: In practice, modern computers do poorly with
   pointer-heavy data structures and well with flat regions
   of memory.
 - Problem: Implementing trees correctly can be really complex.
 - Trees do tend to be used in cases where you want an *ordered*
   key value map structure.
 
### Plan C: Hash Table 
 
 - We're going to put our key value pairs in an array.
 - To avoid linear scan to find items, we use a hash function.
   - Hash function maps key values to an integer, which can
     be turned into an array index.
 - Operations are constant time with no collisions.
 - Dealing with collisions are the tricky bit.
 - Once we deal with them, operations are:
   - Amortized, expected constant time (O(1)).
 

