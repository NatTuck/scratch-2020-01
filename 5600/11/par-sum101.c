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
    // One billion
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    long* sums = mmap(0, 10 * sizeof(long), PROT_READ|PROT_WRITE,
                     MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    pid_t kids[10];

    for (long pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // parent, do nothing
        }
        else {
            long i0 = NPP*pp;
            long i1 = i0 + NPP;
            long sum = 0;

            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                    sum += ii;
                }
            }

            sums[pp] = sum;

            munmap(sums, 10 * sizeof(long));
            exit(0);
        }
    }

    long global_sum = 0;
    for (long pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
        global_sum += sums[pp];
    }

    printf("Sum = %ld\n", global_sum);

    munmap(sums, 10 * sizeof(long));
    return 0;
}
