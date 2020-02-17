
# CS3650: Lecture 12

Today's topic: Virtual Memory


## Semaphores

A semaphore is an integer.

 - sem_wait - decrements the integer
   - can't decrement the integer below zero
   - if integer would go below zero, block the process
 - sem_post - increments the integer
   - if anyone's blocked on the semaphore, wake them up and
     give them another chance to decrement
