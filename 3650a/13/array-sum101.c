
#include <stdio.h>
#include <assert.h>

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int _ac, char* _av[])
{
    // A billion
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    long* sums = mmap(0, 10 * sizeof(long), PROT_READ|PROT_WRITE,
                      MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    for (int ii = 0; ii < 10; ++ii) {
        sums[ii] = 0;
    }

    pid_t kids[10];

    for (int pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // do nothing
        }
        else {
            long i0 = NPP*pp;
            long i1 = NPP*pp + NPP;

            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                    sums[pp] += ii;
                }
            }

            exit(0);
        }
    }

    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    long sum = 0;
    for (int ii = 0; ii < 10; ++ii) {
        sum += sums[ii];
    }

    printf("Sum = %ld\n", sum);

    munmap(sums, 10 * sizeof(long));
    return 0;
}
