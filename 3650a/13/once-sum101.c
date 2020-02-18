
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdlib.h>
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
    sem_t* lock = mmap(0, 4096, PROT_READ|PROT_WRITE,
                       MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(lock, 1, 1);

    pid_t kids[10];

    for (int pp = 0; pp < 10; ++pp) {
        if ((kids[pp] = fork())) {
            // do nothing
        }
        else {
            long i0 = NPP*pp;
            long i1 = NPP*pp + NPP;

            long xx = 0;

            for (long ii = i0; ii < i1; ++ii) {
                if (ii % 101 == 0) {
                    xx += ii;
                }
            }

            sem_wait(lock);
            *sum += xx;
            sem_post(lock);

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
