#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct goat {
    char* name;                       // 8 bytes
    float mass; // kilos              // 4 bytes, immediately after
} goat;

void
init_goat(goat* gg, const char* name, float mass)
{
    gg->name = strdup(name);
    gg->mass = mass;
}

goat
copy_goat(goat* gg)
{
    goat hh;
    init_goat(&hh, gg->name, gg->mass);
    return hh;
}

void
cleanup_goat(goat* gg)
{
    free(gg->name);
}

goat
fattest_goat(goat* xs, int nn)
{
    assert(nn > 0);
    // Precondition: No empty goat herds.

    goat fattest = copy_goat(&(xs[0]));
    for (int ii = 1; ii < nn; ++ii) {
        if (fattest.mass < xs[ii].mass) {
            cleanup_goat(&fattest);
            fattest = copy_goat(&(xs[ii]));
        }
    }
    return fattest;
}

int
main(int _ac, char* _av[])
{
    goat herd[4];
    init_goat(&(herd[0]), "Alice", 50);
    init_goat(&(herd[1]), "Bob", 75);
    init_goat(&(herd[2]), "Carol", 60);
    init_goat(&(herd[3]), "Dave", 55);

    goat gg = fattest_goat(herd, 4);
    printf("Fattest goat is: %s\n", gg.name);
    cleanup_goat(&gg);

    for (int ii = 0; ii < 4; ++ii) {
        cleanup_goat(&(herd[ii]));
    }
    return 0;
}
