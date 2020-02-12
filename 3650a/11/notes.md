
# 3650: Lecture 11

Today's topic: Strategies for Challenge 1

Last time: 

 - Redirect example
 - Sort-pipe example

## Assignment Strategy

Grading usually follows this structure:

 - Half the points are the autograder.
   - You gain points for passing tests.
   - Pass half the tests, get half the points.
 - Half the points are manual grading.
   - You lose points for mistakes.
   - On the shell, you lose points for not attempting features.

Strategy:

 - Submit the starter code.
   - Sometimes it passes autograder tests.
 - Implement just enough logic to pass the first test. Submit that.
 - Repeat for each test, or each couple of tests.

It can be *faster* to write simpler versions of the program first.

 - Even if you write more code.
 - This lets you test the rest of the program earlier.

In fact, my #1 tip for programming:

 - Never write more than 20 lines of code without running them.



## Background operator variants

Version one:

```
  (expression) &
```

Version two:

```
  (expression1) & (expression2)
  (expression1) &; (expression2)
```

# Shell Evaluation Plan

Function "eval":

 * Base case: "command arg1 arg2"
   * first, check if the command is a builtin
     * specifically, "cd" or "exit"
     * in this case *don't fork* and handle it specially 
   * fork
   * in child: exec(command, [arg1, arg2])
   * in parent: wait on child
 * Semicolon: "command1; command2"
   * eval(command1)
   * eval(command2)
 * And / Or: "command1 && command2", "command1 || command2"
   * AND
     * exit_status = eval(command1)
     * if (exit_status is 0): eval(command 2)
   * OR
     * The same, except invert the if condition.
 * Background: "command1 &", "command1 & command2"
   * fork
   * in child: exec(command1, ...)
   * in parent: don't wait
   * if second arg: do that
   * idea: is "background?" a parameter in eval()?
 * Redirect: "command1 > file1", "command1 < file2"
   * fork then in child:
     * open fd for redirect file
     * close stdout
     * dup(fd)
     * close(fd)
     * eval(command1)
   * wait, then exit with same exit code

   * saved_stdout = dup(stdout)
   * open fd for redirect file
   * close stdout
   * dup(fd)
   * close(fd)
   * eval(command1)
   * close(stdout)
   * dup(saved_stdout)
   * close(saved_stodut)

   * fork
   * in child: 
     * do the redirect
     * exec(command, [arg1, arg2])
   * in parent: wait on child

   * redirect stdin is the same, except you redirect stdin

  * Pipe: "command1 | command2"
    * make a pipe 
    * for command1: redirect stdout to pipe
    * for command2: redirect stdin from pipe
    * exec commands in children
    * make sure the redirects don't survive in the parent 
 

    * first, fork (1)
      * make a pipe 
      * for command1, fork and in child:
        * close pipe read fd
        * redirect stdout to pipe write fd
        * eval(command1)
      * for command2, fork and in child,
        * close pipe write fd
        * redirect stdin from pipe read fd
        * eval(command2)
      * wait on both command1 and command2 children
      * exit to propagate exit code
    * wait on child (1)


## Fgets, scanf, read, write

 * What if you mix read and fgets?
   * Bad idea
   * syscalls don't buffer; stdio does
 * Stdio buffering
   * If the stream is interactive (e.g. the terminal), it's line buffered.
   * If the stream is non-interactive (e.g. a file, or a stream redirected
     to a file) it's block buffered.
 * getc / ungetc

Building a buffer: 

 * A buffer is an array of char.
   * Associated size, capacity.
   * Common implementation is a ring buffer, where there are two pointers
     indicating the beginning and end of the data, treating the buffer as
     circular.
 * When the user does a read (e.g. with getc, fgets), try to satisfy it from the
   buffer.




