
#include <stdio.h>
#include <stdlib.h>

// An empty list is a null pointer.
typedef struct int_list {
    int head;
    struct int_list* tail;
} int_list;

int_list*
cons(int xx, int_list* xs)
{
    int_list* ys = malloc(sizeof(int_list));
    ys->head = xx;
    ys->tail = xs;
    return ys;
}

void
free_list(int_list* xs)
{
    if (xs) {
        free_list(xs->tail);
        free(xs);
    }
}

int_list*
reverse(int_list* xs)
{
    int_list* ys = 0;
    for (int_list* curr = xs; curr; curr = curr->tail) {
        ys = cons(curr->head, ys);
    }
    return ys;
}

int_list*
insert(int_list* xs, int xx)
{
    // Precondition: xs is sorted.

    if (xs == 0) {
        return cons(xx, 0);
    }
    else {
        if (xx < xs->head) {
            return cons(xx, xs);
        }
        else {
            return cons(xs->head, insert(xs->tail, xx));
        }
    }
}

int_list*
isort(int_list* xs)
{
    if (xs == 0) {
        // empty?(xs)
        return 0;
    }
    else {
        // (cons first rest)
        return insert(isort(xs->tail), xs->head);
    }

}

int_list*
read_ints(int nn)
{
    int_list* ys = 0;
    int y;

    for (int ii = 0; ii < nn; ++ii) {
        scanf("%d", &y);
        ys = cons(y, ys);
    }

    int_list* zs = reverse(ys);
    free_list(ys);

    return zs;
}

void
print_list(int_list* xs)
{
    for (int_list* curr = xs; curr; curr = curr->tail) {
        printf("%d ", curr->head);
    }
    printf("\n");
}

int
main(int _ac, char* _av[])
{
    int nn;
    printf("How many ints?\n");
    scanf("%d", &nn);

    int_list* xs = read_ints(nn);

    printf("Unsorted list:\n");
    print_list(xs);

    int_list* ys = isort(xs);
    free_list(xs);

    printf("Sorted list:\n");
    print_list(ys);
    free_list(ys);
    return 0;
}
