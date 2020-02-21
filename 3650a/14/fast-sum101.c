#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>

const int NN = 10;

typedef struct sum_job {
    long r0;
    long r1;
    long sum;
} sum_job;

void*
sum_range_thread(void* arg)
{
    sum_job* job = (sum_job*)arg;

    long sum = 0;
    for (long ii = job->r0; ii < job->r1; ++ii) {
        if (ii % 101 == 0) {
            sum += ii;
        }
    }

    job->sum = sum;
    return job;
}

pthread_t
spawn_sum_range(long r0, long r1)
{
    sum_job* job = malloc(sizeof(sum_job));
    job->r0 = r0;
    job->r1 = r1;

    pthread_t thread;
    int rv = pthread_create(&thread, 0, sum_range_thread, job);
    assert(rv == 0);
    return thread;
}

int
main(int _ac, char* _av[])
{
    const long TOP = 1000000000; // a billion
    const long NPP = TOP / NN;

    pthread_t threads[NN];

    for (long pp = 0; pp < NN; ++pp) {
        threads[pp] = spawn_sum_range(pp*NPP, (pp+1)*NPP);
    }

    long sum = 0;
    for (long pp = 0; pp < NN; ++pp) {
        sum_job* job;
        int rv = pthread_join(threads[pp], (void**) &job);
        sum += job->sum;
        free(job);
        assert(rv == 0);
    }

    printf("Sum = %ld\n", sum);

    return 0;
}
