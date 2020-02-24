#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

#define NN 10

// this is really an int -> int function.
void*
thread_main(void* thread_arg)
{
    int xx = *((int*)thread_arg);

    printf("thread %d: We're in a thread.\n", xx);
    xx += xx;

    int* ret = thread_arg;
    *ret = xx;
    return (void*) ret;
}

int
main(int _ac, char* _av[])
{
    int rv;
    pthread_t threads[NN];
    int nums[NN];

    printf("main: Starting %d threads\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        int* arg = &(nums[ii]);
        //int* arg = malloc(sizeof(int));
        *arg = ii;
        rv = pthread_create(&(threads[ii]), 0, thread_main, arg);
        assert(rv == 0);
    }

    printf("main: Started %d threads\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        void* ret;
        rv = pthread_join(threads[ii], &ret);
        int yy = *((int*)ret);
        //free(ret);
        printf("Thread #%d returned %d\n", ii, yy);
        assert(rv == 0);
    }

    printf("main: all threads joined\n");

    return 0;
}
