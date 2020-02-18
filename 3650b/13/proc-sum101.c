#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int _ac, char* _av[])
{
    // A billion
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    long* sum = mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
                     MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *sum = 0;

    pid_t kids[10];

    for (int pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // do nothing
        }
        else {
            long i0 = pp * NPP;
            long i1 = i0 + NPP;

            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                    *sum += ii;   //  Process 1                 Process 2
                                  //    ii = 101                  ii = 202
                                  //
                                  // mov (%sum), %tmp
                                  //    mov 0, %tmp
                                  //                            mov (%sum), %tmp
                                  //                               mov 0, %tmp
                                  // add %ii, %tmp
                                  //    %tmp = 101
                                  //                            add %ii, %tmp
                                  //                               %tmp = 202
                                  // mov %tmp, (%sum)
                                  //   saved 101
                                  //                            mov %tmp, (%sum)
                                  //                               save 202
                }
            }

            exit(0);
        }
    }

    for (int pp = 0; pp < 10; ++pp) {
        waitpid(kids[pp], 0, 0);
    }


    printf("Sum = %ld\n", *sum);

    munmap(sum, sizeof(long));
    return 0;
}
