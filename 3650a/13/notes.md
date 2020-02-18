
# Problem: Data Races

Conditions for a data race:

 - Concurrent execution of multiple processes or threads.
 - The processes must share some data (read or write).
 - At least one process must write.

One plan to fix data races: Locks

The lock rule:

 - Every piece of shared data has an associated lock.
 - When the shared data is accessed the accessing process must hold the lock.

Problems with locks:

 - If you're not careful, locks make your program sequential.
 - If you have more than one lock, your program can deadlock. 
 
Conditions for deadlock:

 - Circular wait.


Avoiding deadlock with locks:

 - Deadlock can *only* be avoided by programmer-enforced programming
   conventions.
 - Convention idea: Never hold more than one lock.
 - Convention idea: Lock ordering

Lock ordering:

 - Define a single global order for all locks in your program.
 - You may not take a lock if you're already holding a lock that
   comes before it in the ordering.

