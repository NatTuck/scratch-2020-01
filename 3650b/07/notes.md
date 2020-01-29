
# CS3650 Lecture 7

Today's Topic: Data Structures in C

## HW04


## The Two Important Data Structures

 - Vectors         - ArrayList
 - Hash Maps       - Map

## Vectors, or Dynamic Arrays, or ArrayLists

Problem: We only have two building blocks for data structures in C.

 - Arrays
 - Structs

To solve:

 - Arrays are static size.

Existing array features:

 - Get item by index.
   - With array indexing (base + index * element size)
 - Put item by index.
   - Again, array structure is good.

New feature:

 - Push back: Add an item to the end of the array, resizing if
   needed.

## Initial Implementation

A Vector is a struct (data*, size).

[]
[1]
[1, 2]
[1, 2, 3]

Consider inserting N items into an empty array.

 - This takes O(n^2) operations.
 - 1 + 2 + 3 + ... + n = n*(n+1) / 2

How to solve this?

 - Give a bunch of extra room.
 - Specifically, when we resize we need to resize by a constant
   factor (e.g. double the size of the array).

## New Plan

 - A struct with three fields: (data*, size, capacity).
 - Initial capacity is non-zero (e.g. 2).
 - Every time our array fills up, we double the size.


[-, -]    (size: 0, capacity: 2)
[1, -]
[1, 2]
[1, 2, 3, -]
[1, 2, 3, 4]
[1, 2, 3, 4, 5, -, -, -]
[1, 2, 3, 4, 5, 6, -, -]    (size: 6, capacity: 8)
[1, 2, 3, 4, 5, 6, 7, -]
[1, 2, 3, 4, 5, 6, 7, 8]
[1, 2, 3, 4, 5, 6, 7, 8, -, -, -, -, -, -, -, -]
[1, 2, 3, 4, 5, 6, 7, 8, 9, -, -, -, -, -, -, -]
[1, 2, 3, 4, 5, 6, 7, 8, 9,10, -, -, -, -, -, -]

 - Now it takes O(n) operations to insert n items.









