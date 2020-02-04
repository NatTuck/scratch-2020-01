
# CS3650

Today's Topic: Hash Tables

## Ways to build a key-value Map

### Plan A: Association list.

 - A list of (key, value) pairs.
 - Problem: Most operations are O(n).

### Plan B: Use a balanced tree

 - Probably a balanced binary tree (e.g. a Red-Black tree)
 - Advantage: Most operations are O(log n).
 - Disadvantages?
   - Modern computer memory heirarchies prefer linear
     data layouts.
   - Writing a correct balanced tree is *annoying*.

### Plan C: Hash Table

 - Have one array of slots where you could put a key value pair.
 - Use a hash function to map key to array slot.
   - Complication: Collisons 
 - Once we figure out all the complicaitons:
   - Operatoins are expected, amortized O(1).









