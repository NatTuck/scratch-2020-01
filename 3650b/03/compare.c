#include <stdio.h>
#include <stdlib.h>

/*
 *    ./compare 2 3
 *    2 <= 3
 *
 *    ./compare 3 2
 *    2 > 3
 */

int
main(int argc, char* argv[])
{
    if (argc != 3) {
        puts("Usage: ./compare NN NN");
        return 1;
    }

    long aa = atol(argv[1]);
    long bb = atol(argv[2]);

    if (aa > bb) {
        printf("%ld > %ld\n", aa, bb);
    }
    else {
        printf("%ld <= %ld\n", aa, bb);
    }

    return 0;
}
