
#include <stdio.h>

typedef struct Cell {
    long head;
    struct Cell* tail;
} Cell;

Cell* cons(long x, Cell* xs);
long car(Cell* xs);
Cell* cdr(Cell* xs);
void free_list(Cell* xs);

int
main(int _ac, char* _av)
{
    Cell* xs = cons(5, cons(4, cons(3, cons(2, cons(1, 0)))));

    long yy = 0;
    for (Cell* pp = xs; pp; pp = pp->tail) {
        yy += pp->head;
    }

    printf("sum = %ld\n", yy);

    return 0;
}
