
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

list*
cons(char* xx, list* xs)
{
    list* ys = malloc(sizeof(list));
    ys->head = strdup(xx);
    ys->tail = xs;
    return ys;
}

void
free_list(list* xs)
{
    if (xs) {
        free(xs->head);
        free_list(xs->tail);
        free(xs);
    }
}

void
print_list(list* xs)
{
    for (; xs; xs = xs->tail) {
        printf(" - %s\n", xs->head);
    }
}

long
length(list* xs)
{
    long nn = 0;
    for (; xs; xs = xs->tail, ++nn);
    return nn;
}

list*
reverse(list* xs)
{
    list* ys = 0;
    for (; xs; xs = xs->tail) {
        ys = cons(xs->head, ys);
    }
    return ys;
}

list*
rev_free(list* xs)
{
    list* ys = reverse(xs);
    free(xs);
    return ys;
}
