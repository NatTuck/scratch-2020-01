
# CS3650: Lecture 3

In case you missed it: http://khoury.neu.edu/home/ntuck



# How to Write Assembly Programs

## Overview

 1. An assembly (or C) program is a collection of functions.
 2. If you write all the functions, the program is done.

The plan:

 1. Start by figuring out the functions (or at least some of the
    functions) that you need.
 2. You always need a "main" function.
 3. Write those functions.
 4. As you discover new functions you need, add them to the list.

## Design Recipe for an Assembly Function

 1. Signature

This is just the function declaration in C.

 2. Pseudocode

Probably the easiest Pseudocode is:

 - Working C code.
 - Almost working C code.

 3. Variable Mappings
 
Two important features in high level languages:

 - Local variable scoping.
 - Local variable names.

For each variable in the pseudocode, figure out where 
it lives in the assembly code (e.g. register? stack?) and
write down that mapping.

 4. Skeleton

```
label:
    ... push used safe registers in order
    enter $XX, $0

    # TODO: Write function body.

    leave
    ... pop used safe registers reverse order
    ret
```


Enter and leave are:

```
# enter $XX, $0 is:
push %ebp
mov %esp, %ebp
sub $XX, %esp
(waste 8 clock cycles)


# leave
mov %ebp, %esp
pop %ebp
```



 5. Write the function body

Translate the pseudocode for your function into assembly.

Every C statement translates into a simple pattern in assembly.

Examples:

 * Variable assignments

```
long a = 5;
long b = 3 * a + 1;
```

Variable mapping:

 * a is 0(%rsp)
 * b is 8(%rsp)
 * (3 * a) %r11
 
```
# long a = 5;
mov $5, 0(%rsp)

# long b = 3 * a + 1;
mov 0(%rsp), %r11
imul $3, %r11
mov %r11, 8(%rsp)
inc 8(%rsp)
```


 * Function calls
 * Conditional statements (if {})
 * Conditional (if {} else {})
 * While loops
 * do ... loops 
 * For loops
 * Switch



