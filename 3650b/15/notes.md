
# CS3650: More Threads

## Sample sort, quickly

To sort an array in parallel with P processes:

 - Step 1: Partition the input into P chunks
   - Data in these chunks are relatively ordered.
 - Step 2: Sort each chunk sequentially in a separate process.
   - If the sort is in place, there's no more work.

Partitioning:

 - Sample
 - Sort the sample
 - Find the pivots
 
Once we have the pivots, each process can take its own chunk data.

## Parallel vs. Concurrent

Concurrent: Two things happen logically at the same time. Either we don't know
what order they occur in, we don't care, or they actually happen simultenously.
This is a program design question. This makes programs potentially harder to
reason about - or easier if that's what makes sense for the program.

Parallel: Two things happen physically at the same time. This is a hardware
question: there need to be two separate pieces of execution hardware to get
parallel execution. This makes programs run faster.

## Threads vs. Processes

We now have two ways to do things concurrently:

 - fork() gets us a process
 - pthread_create() gets us a threads

The big difference is shared memory

 - Threads share by default
 - Processes don't

# History of Concurrency

Back in the day, computers ran a single program at once.

 - Business / academic systems, e.g. minicomputers, this is 1975.
 - Personal computers, e.g. microcomputers, this is 1985.

## Multiprocessing in Industry / Academia

Computers were always a shared resource.

Batch processing evolved into time-sharing, where multiple terminals
(keyboard + screen) connect to the same computer.

This lead to the UNIX operating system, which had to solve some problems:
 
 - Users wrote buggy programs - those shouldn't crash the machine or programs
   being run by other users.
   - Inter-process isolation by virtual memory.
 - Users shouldn't be allowed to hog the CPU.
   - Pre-emptive scheduling.
 - Result: Processes are the unit of concurrency.


## Multiprocessing in Personal Computers

Computers were only rarely a shared resource, and even then not shared
simultaneously.

This leads to the early Windows and Mac OS operating systems.

Main reason for concurrency: GUI applications, multiple windows from different
apps on the screen at the same time

We want interactivity:

 - Can click a mouse or get a network event and respond quickly.
 - Solution: Cooperative scheduling and threads.


## Modern Operating Systems

Desktop computers got more modern in 1995. Windows 95 did pre-emptive
multitasking and virtual memory based isolation.

Server/workstation OS designs had won by ~2000. Mac OS X is UNIX, Windows XP is
based loosely on VMS.

## Multi-Core Processors

Multi-processor systems were available from ~1995, in servers and workstatoins.

Normal consumer machines started being multi-core around 2003.

 - Windows had an obvious way to support this: Threads
   - Windows still doesn't really use processes for single application
     parallelism.
   - Threads are definitely faster on windows
 - Linux had an obvious way to support this: Processes
   - Linux didn't have support for parallel execution of threads until ~2005.
   - Threads are just proceses with a shared address space.
   
   
   
   
   
   
