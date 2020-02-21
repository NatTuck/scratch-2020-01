#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#define NN 10

void*
thread_main(void* thread_arg)
{
    int xx = *((int*)thread_arg);
    //free(thread_arg);

    int yy = 10 * xx;
    printf("in thread: xx = %d, yy = %d\n", xx, yy);
    int* thread_ret = thread_arg; //malloc(sizeof(int));
    *thread_ret = yy;
    return thread_ret;
}

int
main(int _ac, char* _av[])
{
    int rv;
    pthread_t threads[NN];

    int nums[NN];

    printf("main: starting %d threads\n", NN);

    for (int ii = 0; ii < NN; ++ii) {
        //int* thread_arg = malloc(sizeof(int));
        int* thread_arg = &(nums[ii]);
        *thread_arg = ii;
        rv = pthread_create(&(threads[ii]), 0, thread_main, thread_arg);
        assert(rv == 0);
    }

    for (int ii = 0; ii < NN; ++ii) {
        int* ret;
        rv = pthread_join(threads[ii], (void**) &ret);
        printf("Joined thread %d, ret = %d\n", ii, *ret);
        // free(ret);
    }

    printf("main: all threads joined\n");
    return 0;
}
