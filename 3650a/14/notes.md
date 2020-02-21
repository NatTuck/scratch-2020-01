
# CS3650

## Data Races & Deadlocks

Conditions for a data race:

 - Concurrent execution
 - Shared memory
 - One process needs to write to the shared memory

Using locks:

 - Each piece of shared data has an associated lock.
 - Any process accessing the shared data must hold the lock.

Conditions for a deadlock:

 - Circular wait

e.g.

 - Having more than one lock.

Avoiding deadlock:

 - Never hold more than one lock.
 - Lock ordering.


## Semaphores

A semaphore is an integer, with two associated operations:

 - wait: Attempt to decrement the value. If this would bring the value below
         zero, block until an increment happens (at which point retry).
 - post: Increment the value.

If we start with a value of 1, that's a lock.

If we start with a value of 0, we can block until a future event.

If we start with a value >1, we can allow a fixed number of processes
to do something at once.












