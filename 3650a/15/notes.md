
# CS3650 

## Threads vs. Processes

Two ways to get parallel / concurrent execution:

 - Processes
 - Threads
 
Key difference: shared address space for threads

## Parallelism and Concurrency

 - Concurrency is when two things logically happen at the same time. Either we
   can't assign an order, or we don't care about the order. This is a question
   about software design.
 - Parallelism is when two things physically happen simultaneously. This is
   really a hardware property.

## History

Early computers could run one thing at a time.

Multi-processing let you run more than one application at once.

 - First in commercial / academic minicomputers.
 - Initial plan: batch processing 
   - Improved with timesharing, multiple terminals
   - Multiple users means we need isolation for reliability.
   - The solution was processes with pre-emptive multitasking.

Personal computers got multiprocessing in the mid 80's.

 - Personal computers need concurrency for GUIs.
 - They *don't* need isolation for reliability.
 - The solution was cooperative multi-tasking and threads.

These plans collided around the mid 90's (e.g. Windows 95), and were solidified
around the year 2000 with Mac OS X and Windows XP.

Around 2004 we got dual-core CPUs.

 - Unix style systems supported this great: Multiple processes could run
   on multiple cores.
 - Windows style systems supported this great: Multiple threads could run
   on multiple cores.

Linux got real parallel threads around 2004. Threads were just processes without
creating a new address space.

Today, parallelism is nessisary for performance.
