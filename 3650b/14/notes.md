
# CS3650

## Review: Data Races & Deadlock

Conditions for a data race:

 - Multiple concurrent processes (or threads)
 - Shared memory (reads or writes)
 - At least one concurrent process writes

Locks:

 - Each piece of shared data has an associated lock.
   - Possibly many pieces of data per lock.
 - Whenever the shared data is accessed, the accessing process holds the lock.

Conditions for a deadlock;

 - Circular wait.

Avoiding deadlock:

 - Never hold more than one lock.
 - Lock ordering.


# Semaphores

A semaphore is an integer, with two associated operations:

 - wait: Attempt to decrement the value. If that would bring the value
         below zero, block until incremented and then retry.
 - post: Increment the value, waking up anyone who's blocked so they
         can retry their decrement.

If we start with an integer value of 1, we have a lock:

 - wait is the lock operation
 - post is the unlock operation

If we start with an integer value of 0, we can block until a later event.

If we start with an integer value of >1, we have a multi-lock structure
which isn't obvoiusly useful.








