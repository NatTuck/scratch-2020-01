
## Problem: Data Races

Conditions for a data race:

 - Concurrent execution of multiple processes or threads.
 - Concurrent access to shared memory (read or write)
 - At least one process must write.

Standard solution: Locks

 - Each piece of shared data must have an associated lock.
 - That lock must be locked by the current process whenever
   it access the shared data.

Problems with locks:

 - Locks can serialize program execution.
 - If you have at least two locks, you've got a deadlock problem.

Solving deadlock:

 - The only way to solve deadlock is through programmer-enforced
   universal programming conventions. 

Sample convention:

 - Never hold more than one lock at a time.
 - Declare a universal global order for all locks in the program. Never lock a
   lock if you've already locked one that comes later in the ordering.


So this is the great problem of software development today.





