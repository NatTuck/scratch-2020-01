
#include <stdio.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

sem_t*
make_lock()
{
    sem_t* lock = mmap(0, sizeof(long), PROT_READ|PROT_WRITE,
                       MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(lock, 1, 1);
    return lock;
}

int
main(int _ac, char* _av[])
{
    //int aa_data; // assume this is shared
    sem_t* aa = make_lock();

    //int bb_data; // assume this is shared
    sem_t* bb = make_lock();

    int cpid;
    if ((cpid = fork())) {
        // do some prep work on aa
        printf("Ready to work in parent.\n");
        sem_wait(aa);
        sleep(1);
        printf("parent: done with prep\n");

        sem_wait(bb);
        printf("parent: combining\n");
        // do some work combining aa with bb atomicly with the prep work
        sem_post(bb);
        sem_post(aa);
        printf("parent: done\n");
    }
    else {
        // do some prep work on bb
        printf("Ready to work in child.\n");
        sem_wait(aa);
        sem_wait(bb);
        sleep(1);
        printf("child: done with prep\n");

        //sem_wait(aa);
        printf("child: combining\n");
        // do some work combining bb with aa atomicly with the prep work
        sem_post(aa);
        sem_post(bb);
        printf("child: done\n");
    }
    return 0;
}
