

# 5600: Lecture 4

Today's topic: Introducing System Calls


The operating system controls access to shared resources, by:

 1. User programs can't directly access shared resources.
 2. Providing an interface that programs can use to safely access
    shared resources - this interface is: system calls.

A system call is kind of like a function call, except instead of
executing normal code elsewhere in your program's memory space, it
causes privledged kernel code to run.

## What syscalls do we have?



## Doing an AMD64 syscall

 - Fill in syscall # in %rax
 - Fill in args
 - Do "syscall"

## Doing an i386 syscall

 - Fill in syscall # in %eax
 - Fill in args (%ebx, %ecx, ...)
 - Do "int $0x80"

## System calls from C

 - These appear in section 2 of the manual.

Example:

```
$ man 2 write
$ man 2 exit
```

## Standard File Descriptors

When a program starts up on Linux, it gets three file descriptors
automatically.

 - 0: stdin
 - 1: stdout
 - 2: stderr

If you open more files, it starts slotting them into the file table
starting from #3.


# Some notes on arrays and pointers in C

 - Arrays in C are just like in ASM.
 - Array variables store the address of the start of the array.
 - C knows how big the type stored in the array is.
 - A pointer is a variable that stores a memory address with an
   associated type.
 - Pointers and arrays are pretty much the same thing.
 - C lets you do arithmetic with pointers.

```
int xs[] = {0,1,2,3};
int* x0a = &(xs[0]);

int* x1a = x0a + 1;
print *x1a;
```













