
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

// Here's our stack.
int stack[5];
int sp = 0; // what index do we put the next pushed item it
pthread_mutex_t lock;
pthread_cond_t  cond;

void
stack_push(int xx)
{
    // Precondition: There must be at least one free slot on the stack.
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
    // Precondition: There must be at least one item on the stack.
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
    sleep(2);
    for (int ii = 0; ii < 500; ++ii) {
        stack_push(ii);
    }
    return 0;
}

int
main(int _ac, char* _av[])
{
    pthread_mutex_init(&lock, 0);

    pthread_t threads[2];

    for (int ii = 0; ii < 2; ++ii) {
        int rv = pthread_create(&(threads[ii]), 0, producer_thread, 0);
        assert(rv == 0);
    }

    for (int ii = 0; ii < 1000; ++ii) {
        int yy = stack_pop();
        printf("%d\n", yy);
    }

    for (int ii = 0; ii < 2; ++ii) {
        int rv = pthread_join(threads[ii], 0);
        assert(rv == 0);
    }

    return 0;
}
