#include <stdio.h>
#include <assert.h>

int
main(int _ac, char* _av[])
{
    const long TOP = 1000000000; // a billion

    long sum = 0;
    for (long ii = 0; ii < TOP; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }

    printf("Sum = %ld\n", sum);

    return 0;
}
