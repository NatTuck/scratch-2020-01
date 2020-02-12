
# CS 5600, lecture 11: Data Races



## Conditions for a Data Race

 - Two processes (or threads) executing concurrently
 - Shared memory (reads or writes)
 - At least one process does a write.

## Conditions for a Deadlock

 - Circular wait
 
## Data Races in HW06

Barriers:

 - One key operatoin: barrier_wait
 - No process can proceed past the barrier until every process
   has gotten to the barrier.

This can solve data races. For example, if unshared writes only occur before
the barrier and shared reads only occur after, then those reads can't be a data
race with the writes.



