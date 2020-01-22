
# 5600 Lecture 5

Using a struct from assembly:

 - Find the size so you can allocate it.
   - Test C program.
   - Make an instance of that struct
   - Call sizeof() on it.
 - Find the offset of the field you need.
   - Find the address of the struct.
   - Find the address of the field.
   - The difference is the offset.

## Next Topic: Working with an OS kernel

 - Our sample OS: xv6


## Interrupts

Two kinds:

 - Hardware
 - Software

Hardware interrupts:

 - Physical wire from hardware.
 - WHen signaled, CPU stops what it's doing
 - CPU looks in trap vector
 - Every interrupt has an interrupt number, x.
 - CPU looks in trap_vector[x] for code pointer.

Software interrupts:

 - Triggered by the "int" instruction.
 - Otherwise similar.
 - Usually can't be triggered by user code, but can
   be configured so that's allowed for specific interrupt numbers.
 
Assembly:

```
    push %eax
    push %ecx
    push %esp
    call foo
```

```
struct info {
    int ecx;
    int eax;
};

void foo(struct info* in)
{


}
```


## xv6 add syscall

 - Notes are missing addition to usys.S





