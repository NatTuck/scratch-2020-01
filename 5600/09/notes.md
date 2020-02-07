
# 5600: More on Threads

The problem with threads / concurrency:

 - Modern computers are multi-core.
 - If we care about performance, we need parallel code.
 - Parallel code implies concurrent code.

Your code has data races if:

 - Concurrent execution
 - Shared data between threads (or processes)
 - Any thread writes to the shared data

At that point we can assume that our program is broken unless
clearly proven to be OK.

One way to fix data races is locks.

The lock rule:

 - Each piece of shared data has an associated lock.
 - All access (read or write) of the shared data is protected by the lock.

Unfortunately, if we have two or more locks, we risk deadlock.

Deadlock is only solved by manually enforced programming conventions:

 - e.g. Never hold more than one lock.
 - e.g. Enforce program-wide lock ordering.
 - e.g. Always take all your locks at once with std::lock_guard in C++.

We got to Schedulers slide 43.






