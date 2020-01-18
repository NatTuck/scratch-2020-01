
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage:\n  %s N, where N > 0\n", argv[0]);
        return 0;
    }

    printf("fib(%ld) = %ld", atol(argv[1]), atol(argv[1]));
    return 0;
}
