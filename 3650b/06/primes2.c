
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long
sqrt_up(long xx)
{
    return (long)ceil(sqrt(xx));
}

/* Precondition:
 * primes[] contains all the primes up to sqrt(xx), plus an extra one
 */
int
is_prime(long* primes, long xx)
{
    // Plan A: If xx is divisible by no smaller number, it's prime.
    // Plan B: Only check smaller prime numbers.
    // Plan C: Stop at sqrt(xx)
    // Skip evens.
    //
    // Array indexing in C (like xx[yy]) is defined as
    //    *(xx + yy).
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
{
    long primes[nn < 5 ? 5 : nn];
    for (long ii = 0; ii < nn; ++ii) {
        primes[nn] = 0;
    }

    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;

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
        puts("Usage: ./prime NN");
        puts("  prints the NN'th prime number");
        return 1;
    }

    long nn = atol(argv[1]);
    long pp = prime(nn);

    printf("The %ld'rd prime is %ld\n", nn, pp);

    return 0;
}
