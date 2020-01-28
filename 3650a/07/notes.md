
# CS 3650: Lecture 7

Today's topic: Data Structures in C


## Two Most Common Data Structures

 - Dynamic Arrays        - vector, ArrayList, Array
 - Associative Arrays    - HashMap, Map

## Vectors

C gives us two building blocks for structured data:

 - Arrays
 - Structs

Any other data structure we need to build ourselves.

Building variable length arrays.

 - Problem: Arrays are fixed length.
   - Arrays don't even know their own length.
 - Solution: Start with a small array, reallocate bigger
   arrays when you run out of space.

What functionality do we need?

  Normal array operations:
  
   - Get length.
   - Get by index. (like x = xs[ii])
   - Put by index. (like xs[ii] = x)
   - "Push back", where we add an item to the end and grow
     if needed.

Additoinal requirements:

 - Array should be contiguous in memory.
   - Reason 1: it's faster
   - Reason 2: It's compatible with existing array functions
   
First implementation:

 - struct {data[], size}
 - To push an item, allocate a new data array of size (n+1) and
   copy over N items.

Problem: Filling an array of n items takes n^2 time.

Improvement: Don't just grow by 1 at a time.

 - Struct has three fields (data[], size, capacity)
   - capacity >= size
 - Start with size = 0, capacity = 2 (or 4, or ...)
 - When reallocation is required, double capacity.

Example:

We're going to push 1..10 onto our array.

[-, -]   (capacity: 2, size: 0)
[1, -]   (capacity: 2, size: 1)
[1, 2]
[1, 2, 3, -]
[1, 2, 3, 4]
[1, 2, 3, 4, 5, -, -, -]   (capacity: 8, size: 5)
[1, 2, 3, 4, 5, 6, -, -]
[1, 2, 3, 4, 5, 6, 7, -]
[1, 2, 3, 4, 5, 6, 7, 8]
[1, 2, 3, 4, 5, 6, 7, 8, 9, -, -, -, -, -, -, -]
[1, 2, 3, 4, 5, 6, 7, 8, 9,10, -, -, -, -, -, -]

- Now inserting N items takes O(N) time.
- Yes, it's a pyramid scheme.
























