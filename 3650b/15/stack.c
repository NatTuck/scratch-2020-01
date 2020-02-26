#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

const int NN = 2000; // numbers produced per thread
const int PP = 5;   // # of threads

int stack[5];
int sp = 0; // the index where we can insert the next item
pthread_mutex_t lock;
pthread_cond_t  cond;

void
stack_push(int xx)
{
    // precondition: stack isn't full
    pthread_mutex_lock(&lock);
    while (sp > 4) {
        pthread_cond_wait(&cond, &lock);
    }
    stack[sp++] = xx;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
}

int
stack_pop()
{
    // precondition: stack isn't empty
    pthread_mutex_lock(&lock);
    while (sp <= 0) {
        pthread_cond_wait(&cond, &lock);
    }
    int yy = stack[--sp];
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
    return yy;
}

void*
producer_thread(void* _arg)
{
    for (int ii = 0; ii < NN; ++ii) {
        stack_push(ii);
    }
}

int
main(int _ac, char* _av[])
{
    pthread_mutex_init(&lock, 0);

    pthread_t threads[PP];
    int rv;

    for (int ii = 0; ii < PP; ++ii) {
        rv = pthread_create(&(threads[ii]), 0, producer_thread, 0);
        assert(rv == 0);
    }

    for (int ii = 0; ii < (NN * PP); ++ii) {
        printf("%d\n", stack_pop());
    }

    for (int ii = 0; ii < PP; ++ii) {
        rv = pthread_join(threads[ii], 0);
        assert(rv == 0);
    }

    return 0;
}
