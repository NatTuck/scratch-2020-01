
# 3650 Lecture 5

```
    .data
msg: .string "hello"

    .text
foo:
    enter $0, $0
   
    mov $msg, %rdi
   
    mov (%rdi), %al
    
    cmp $'h, %al
   
    leave
    ret
```

## Processes and Memory

 - A process is the thing you get when you run a program.

Important parts of an executable file:

 - .text
 - .data
 
Important stuff in memory for new process:

 - .text
 - .data
 - stack
 - heap


Malloc and free.

When you call malloc,

 - call free at least once on that pointer or you leak memory
 - call free at most once on that pointer or undefined behavior
   - undefined behavior could include the program selling your kidneys 
     and shipping them to canada
 
## Dynamic Allocation 

First choice: The Heap

 - Allocate with malloc, free with free.

Second choice: The stack

```
    // Dynamic array sizes
    nn = read_int();
    long xs[nn];

    // Alloca
    long* xs = alloca(nn * sizeof(long)); 
```


```
    mov $15, %r10     // 15  is ....000001111
    not %r10          // ~15 is ....111110000 
    and %r10, %rsp
```

In this concrete program there were two cases:

 - nn is even:
   - Allocate space on stack, new %rsp ends in: ....0000
   - Stack alignment code changes nothing.
 - nn is odd:
   - Allocate space on stack, new %rsp ends in: ....1000
   - Changes stack pointer, reducing it by 8.















