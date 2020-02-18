#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <semaphore.h>

sem_t*
make_lock()
{
    sem_t* lock = mmap(0, sizeof(sem_t), PROT_READ|PROT_WRITE,
                       MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sem_init(lock, 1, 1);
    return lock;
}

int
main(int _ac, char* _av[])
{
    //int aa_data = ... shared data
    sem_t* aa = make_lock();

    //int bb_data = ... shared data
    sem_t* bb = make_lock();

    int cpid;
    if ((cpid = fork())) {
        // first, do some work with aa_data to prep it
        printf("in parent\n");
        sem_wait(aa);
        printf("parent: preparing aa_data\n");
        sleep(1);

        // then, combine aa_data and bb_data atomically with the prep work
        sem_wait(bb);
        printf("parent: combining aa_data with bb_data\n");
        printf("parent: done\n");
        sem_post(bb);
        sem_post(aa);
    }
    else {
        // first, do some work with bb_data to prep it
        printf("in child\n");
        sem_wait(aa);
        sem_wait(bb);
        printf("child: preparing aa_data\n");
        sleep(1);

        // then, combine aa_data and bb_data atomically with the prep work
        printf("child: combining aa_data with bb_data\n");
        printf("child: done\n");
        sem_post(aa);
        sem_post(bb);
    }

    return 0;
}
