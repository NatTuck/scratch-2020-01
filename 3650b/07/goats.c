#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct goat {
    char* name;                     // 8 bytes
    float mass;   // in kilos       // 4 bytes
} goat;

// sizeof(goat) = 12
//   maybe = 16, if there's padding

void
init_goat(goat* gg, const char* name, float mass)
{
    gg->name = strdup(name);
    gg->mass = mass;
}

void
cleanup_goat(goat* gg)
{
    free(gg->name);
}

goat
copy_goat(goat* gg)
{
    goat hh;
    init_goat(&hh, gg->name, gg->mass);
    return hh;
}

goat
fattest_goat(goat* xs, int nn)
{
    assert(nn > 0);

    goat x = copy_goat(&xs[0]);
    for (int ii = 0; ii < nn; ++ii) {
        if (xs[ii].mass > x.mass) {
            x = copy_goat(&xs[ii]);
        }
    }
    return x;
}

int
main(int _ac, char* _av[])
{
    goat herd[4];
    init_goat(herd + 0, "Alice", 50);
    init_goat(herd + 1, "Bob", 75);
    init_goat(herd + 2, "Carol", 60);
    init_goat(herd + 3, "Dave", 55);

    goat gg = fattest_goat(herd, 4);
    printf("Fattest goat is: %s\n", gg.name);
    cleanup_goat(&gg);

    for (int ii = 0; ii < 4; ++ii) {
        cleanup_goat(&(herd[ii]));
    }

    return 0;
}

