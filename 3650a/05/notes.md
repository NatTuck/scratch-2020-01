
# CS3650: Lecture 5

A process is a running program.


## Areas of memory

 - .text
 - .data
 - stack
 - heap
 
## Dynamic memory allocation

Plan A: The Heap
 
 - To get N bytes of memory: x = malloc(N)
 - When we're done with it: free(x)
 - If you forget to free stuff, you have a memory leak.
 - If you free something twice, that's undefined behavior and things
   will break.
   - A program executing undefined behavior can do *anything*.
   - Hopefully it crashes, but probably it'll do something you don't want.

Plan B: The Stack

 - You allocate space on the stack by subtracting from the stack
   pointer.
 - This is handled automatically by the C compiler for static sized
   objects.
 - The C compiler can even do dynamically-sized arrays.

```
int 
sort(int* xs, int nn)
{
    int temp[nn];
    ...
}
```

```
int 
sort(int* xs, int nn)
{
    int* temp = alloca(nn * sizeof(int));
    ...
}
```



```
    mov $15, %r10
    not %r10
    and %r10, %rsp
```

 * 15 is ...00000001111
 * not 15 is ...111111110000
 * %rsp and ~15 guarantees bottom four bits of %rsp are
   now 0, thus it's a multiple of 16
 * Why is that OK? Never moves stack up, only maybe down.

Concrete example:

 - Allocate an even number of longs:
   - Stack pointer is divisible by 16, ends with 0000 
   - Alignment fix doesn't change anything.
 - Allocate an odd number of longs:
   - Stack pointer is divisible by 8 but not 16: 1000
   - Alignment fix changes that one bit to: 0000
   
 
 






 











