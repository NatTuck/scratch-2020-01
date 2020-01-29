
# CS5600: Lecture 7

Today: Processes and File Descriptors




## Spawning New Programs

On POSIX:

 - Fork
   - Copies the full process state.
   - Logicly including all of memory.
 - In the child, exec


The more obvious API:

 - CreateProcess(path...)
 - That's how Windows does it. 



