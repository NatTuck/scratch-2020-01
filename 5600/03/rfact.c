#include <stdio.h>

long
fact(long x)
{
    if (x <= 1) {
        return 1;
    }
    else {
        return x * fact(x - 1);
    }
}

int
main(int _ac, char* _av[])
{
    long x;
    scanf("%ld", &x);

    long y = fact(x);
    printf("fact(%ld) = %ld\n", x, y);

    return 0;
}
