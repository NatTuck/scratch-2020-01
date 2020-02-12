
## 3650 Lecture 11: More stuff for the shell


### General Assignment Strategy

Assignments mostly work the same:

 - half autograder points
   - You get points for passing tests.
 - half manual grading
   - You lose points for errors
   - On the shell, you lose points for not attempting features

Hard to predict how long HW will take.

Solution: Work on the assignents incrementally.

 - First, download the starter code and then submit it.
 - Next, modify the code to pass the first test, submit that version.
 - Keep working one or a few tests at a time.

Stop when:

 - You're done OR
 - You run out of time OR
 - You get bored

It can be *faster* to build simpler versions of a program first, rather
than trying to build the whole most-complete version on the first try.

The advantage of building the simple version of components first is that you can
get the rest of the components working and tested earlier.

Finally, my #1 recommendation for programming:

 *** Never write more than 20 lines of code without running it. ***


### Shell Evaluation Plan

You're writing a function "eval" which takes an AST and executes it.

 * Base case: "command arg1 arg2"
   - first, check for builtins: "cd", "exit"
     - if so, don't fork
     - do the builtin
   - fork
   - in child: exec(command, [args...])
   - in parent: wait on child
 * Semicolon: "command1; command2"
   - eval(command1)
   - eval(command2)
 * And / Or: "command1 && command2", "command1 || command2"
   - AND:
     - status = eval(command1)
     - if (status == 0): eval(command2)
   - OR:
     - status = eval(command1)
     - if (status != 0): eval(command2)
 * Background "command1 &", "command1 & command2"
   - fork
   - in child: exec(command, [args...])
   - parent: don't wait
 
   - "command1 & command2"
      same as
   - "command1 &; command2"
 * Redirect: "command1 > file1", "command1 < file1"
   - (redirect stdout)
   - fork(), in child:
     - close(1)
     - fd = open(file1, write)
     - dup(fd)
     - close(fd)
     - status = eval(command1)
     - exit(status) 
   - in parent: wait for child
   
   - (redirect stdin)
   - Same except close(0) instead and open for reading

 * Pipe: "command1 | command2"
   - pipe(pipes[])
   - fork (1), in child (1):
     - close(stdout)
     - dup(pipes[1])
     - close(pipes[1], pipes[0])
     - status = eval(command1)
     - exit(status) 
   - fork (2), in child (2)
     - close(stdin)
     - dup(pipes[0])
     - close(pipes[1], pipes[0])
     - status = eval(command2)
     - exit(status) 
   - close both ends of pipe
     - alternatively, do the whole pipe thing in a child
   - wait on both children


