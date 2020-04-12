
# Computer Systems: Solutions for Concurrency and Parallelism

Modern computers are parallel:

 - Haven't been able to buy a single core machine
   for like a decade.

Data races:

 - Concurrent execution
 - Shared data
 - At least one access to the shared data must be
   a write (requires mutability)

Solutions in C:

 - Mutexes
 - Barriers
 - Trickier uses of semaphores
 - Atomic operations

Solutions not in C: How do other programming environments
try to do better?

# Key background: Primitives

 - Everything is built on atomic operations
 - Atomic compare and swap 


   
## Plan A: Restrict Concurrent Execution

Example: JavaScript

Concurrent execution is restricted:

 - No parallelism.
 - Asynchronous functions run atomicly.
 - JavaScript runtime sits in an event loop running
   tasks / event handlers.

## Plan B: Eliminate Shared Data

No concrete example

 - fork()
 - Message passing 
   - Microservices
   - Traditional cluster computing (e.g. MPI)
   - As a pattern (e.g. Go)
 
## Data races

Three conditions

 - Concurrent execution
 - Shared data
 - At least one access to the shared data must be
   a write (requires mutability)
   
Eliminate any one to avoid the data race.

## Plan C: Eliminate Mutability

 - Every functional language.
   - Haskell, Clojure, Objective Caml
 - Example: Elixir
   - Based on Erlang
   - Goal: Reliability
   - Reliability => Hardware Redundancy
   - Hardware Redundancy => Distributed System
   - Erlang's one problem: Syntax
   - Key trick: Processes

## Plan D: Combinations

 - Erlang / Elixir: Restrict mutability *and* shared data.
 - Rust: Restrict mutability *of* shared data.
 
## Plan E: Detect and Fix the Data Race

Example: Clojure

Two strategies in Clojure:

 - Immutable data
 - Software Transactional Memory

