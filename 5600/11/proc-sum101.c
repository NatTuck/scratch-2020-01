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

    long* sum = mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
                     MAP_SHARED|MAP_ANONYMOUS, -1, 0);

    pid_t kids[10];

    for (long pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // parent, do nothing
        }
        else {
            long i0 = NPP*pp;
            long i1 = i0 + NPP;

            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                                // process 2                process 4
                    *sum += ii; // mov (%sum), %tmp
                                // tmp = 0
                                //                          mov (%sum), %tmp
                                //                          tmp = 0
                                // add %ii, %tmp
                                // tmp = 10
                                //                          add %ii, %tmp
                                //                          tmp = 200
                                // mov %tmp, (%sum)
                                // sum = 10
                                //                          mov %tmp, (%sum)
                                //                          sum = 200
                }
            }

            munmap(sum, sizeof(long));
            exit(0);
        }
    }

    for (long pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
    }

    printf("Sum = %ld\n", *sum);

    munmap(sum, sizeof(long));
    return 0;
}
