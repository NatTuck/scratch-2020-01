#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long
sqrt_up(long xx)
{
    return (long)ceil(sqrt(xx));
}

// Precondition:
// All primes up to sqrt(xx) are in primes, plus an extra one.
int
is_prime(long* primes, long xx)
{

    // Plan A: check if it's divisible by any smaller numbers.
    // Plan B: Stop at sqrt(xx)
    // Plan C: Just check smaller primes, stop at sqrt(xx).

    // Array access xx[yy] is defined as
    // pointer arithmetic *(xx + yy).

    for (long ii = 0; ii[primes] <= sqrt_up(xx); ++ii) {
        long pp = ii[primes];
        if ((xx % pp) == 0) {
            return 0;
        }
    }

    return 1;
}

long
prime(long nn)
    // Returns the nn'th prime.
{
    long primes[nn < 2 ? 3 : nn];

    for (long ii = 0; ii < nn; ++ii) {
        primes[ii] = 0;
    }

    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;

    if (nn <= 2) {
        return primes[nn - 1];
    }

    for (long ii = 3; ii < nn; ++ii) {
        long guess = primes[ii - 1] + 2;
        while (!is_prime(primes, guess)) {
            guess += 2;
        }

        primes[ii] = guess;
    }

    return primes[nn - 1];
}


int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("Usage: ./primes NN");
        puts("  prints out the NN'th prime number");
        return 1;
    }

    long nn = atol(argv[1]);

    printf("the %ld'rd prime is: %ld\n", nn, prime(nn));

    return 0;
}
