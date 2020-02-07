
# CS3650: Lecture 10

Today: processes - fork() and exec()


## Combining flags with bitwise OR


const int FLAG1 = 1;
const int FLAG2 = 2;
const int FLAG3 = 4;
const int FLAG4 = 8;

our_syscall(FLAG2 | FLAG4);

FLAG2 | FLAG4 = 2 + 8 = 10

if (flags & FLAG2) {
   // we know flag2 was set
}
