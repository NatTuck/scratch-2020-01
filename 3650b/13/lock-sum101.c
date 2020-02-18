#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <semaphore.h>

int
main(int _ac, char* _av[])
{
    // A billion
    const long TOP = 1000000000;
    const long NPP = TOP / 10;

    long* sum = mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
                     MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *sum = 0;

    sem_t* lock = mmap(0, sizeof(sem_t), PROT_READ|PROT_WRITE,
                       MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(lock, 1, 1);

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
                    sem_wait(lock);
                    *sum += ii;
                    sem_post(lock);

                                  //  Process 1                 Process 2
                                  // mov (%sum), %tmp
                                  // add %ii, %tmp
                                  // mov %tmp, (%sum)
                                  //                            mov (%sum), %tmp
                                  //                            add %ii, %tmp
                                  //                            mov %tmp, (%sum)
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
