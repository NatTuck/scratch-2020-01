#include <stdio.h>

int
main(int argc, char* argv[])
{
    long x;
    scanf("%ld", &x);

    long y = 1;
    for (int ii = x; ii > 0; ii--) {
        y = y * ii;
    }

    printf("fact(%ld) = %ld\n", x, y);
    return 0;
}
