
#include <stdio.h>

// Here's our stack.
int stack[5];
int sp = 0; // what index do we put the next pushed item it

void
stack_push(int xx)
{
    stack[sp++] = xx;
}

int
stack_pop()
{
    return stack[--sp];
}

int
main(int _ac, char* _av[])
{


    for (int ii = 0; ii < 1000; ++ii) {
        stack_push(ii);
    }

    for (int ii = 0; ii < 1000; ++ii) {
        int yy = stack_pop();
        printf("%d\n", yy);
    }

    return 0;
}
