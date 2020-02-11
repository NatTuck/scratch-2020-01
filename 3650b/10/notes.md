
# CS3650: Lecture 10

shell concepts: fork, exec, pipes, redirects



## Using bitwise operators to store flags in integers.

FLAG1 = 1
FLAG2 = 2
FLAG3 = 4
FLAG4 = 8

do_thing(  FLAG2 | FLAG4  );

FLAG2 | FLAG4 = 10

void do_thing(int flags) {
    if ( flags & FLAG2 ) {
        //flag2 is set
    }
}



## Boolean vs Bitwise

a = 1
b = 1
c = 4

a && b = 1
a & b = 1
a && c = 1
a & c = 0

a   = 0001b
c   = 0100b
a&c = 0000b



