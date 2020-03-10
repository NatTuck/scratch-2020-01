
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






