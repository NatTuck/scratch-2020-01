
## CS3650: Lecture 3

If you missed it: http://khoury.neu.edu/home/ntuck


## How to Write an Assembly Program

### Overview

 1. An assembly (or C) program is a bunch of functions.
 2. All we need to do is write those functions.

Step 1: Figure out what functions you need.

 1. Really you only need to figure out some of the functions you
    need so you have a place to start.
 2. We always need a main function, so we can start there.
 3. As you discover more functions, add them to your work queue.
 4. Once you're done with your work queue, your program is done.

Step 2: Apply the recipie below for each function.


### Recipie for an Assembly Function

 1. Signature
 
This is useful, it's also the function header from C. 
 
 2. Pseudocode
 
Better not to start trying to solve the problem in assembly.

Good pseudocode:

 - Working C
 - Not-quite working C
 
 3. Variable Mappings
 
Your pseudocode has named variables. Those are useful, you want to keep them.

For each named variable (or other relevent value), figure out where it lives
in the assembly code and write that down in a comment.

For example:

 - xx is %rbx
 - yy is 8(%rsp)
 
Which registers should we use?

 - There are two pure-temporary registers: %r10, %r11
   - Remember that temporary registers get clobbered when you call
     any function.
 - The first six function arguments are also temporary registers:
   %rdi, %rsi, %rdx, %rcx, %r8, %r9
 - Last temporary is %rax, which is also the return address register.
   - Remember that some *instructions* clobber %rax and %rdx
 - Safe registers: %rbx, %r12-%r15
   - You need to save these in your function prologue before use and restore in
     your epilogue.
 - If you run out of registers, the only other place to put local variabes
   is on the stack.
 
 4. Skeleton

```
label:
   ... push used safe registers in order
   enter $NN, $0

   // TODO: Function body

   leave 
   ... pop used safe registers in reverse order
   ret 
``` 


What are enter / leave exactly?

```
// enter $NN, $0 is:
push %ebp
mov %esp, %ebp
sub $NN, %esp
(waste 8 clock cycles)


// leave is:
mov %ebp, %esp
pop %ebp
```

 5. Write the function body

Translate the function body from your pseudocode into assembly.

C code (and thus your pseudocode) translates about 1:1 into assembly.


### Translating C to Assembly

 - Every C statement translates to an assembly "template".
 - The resulting assembly will perform the same computation, and
   a function translated this way can be compiled into the same C
   program replacing the C function.
 - There are multiple possible templates.

#### Variables, Temporaries, Assignments

```
int a = 5;
int b = 3 * a + 1;
```

Map variables:

 * a is 8(%rsp)
 * b is 16(%rsp)
 * (3*a) in %rax

```
// int a = 5;
mov $5, 8(%rsp)

//int b = 3 * a + 1;
mov 8(%rsp), %rax
imul $3
add $1, %rax
mov %rax, 16(%rsp)
```

## Conditional Statement

```
if (a < 10) {
    do_something()
}
```

Variable mappings:

 - a is %r11

```
    cmp $10, %r11
    jl cond_then
    jmp cond_done

cond_then:
    call do_something

cond_done:
```

```
    cmp $10, %r11
    jge cond_done

// then
    call do_something

cond_done:
```

To think about:

 * while loops
 * for loops
 * do ... while loops
 * if - then - else
 * switch







