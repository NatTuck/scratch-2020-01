
#include <stdio.h>
#include <stdlib.h>

char *msg = "static data";

int
main(int _ac, char* _av)
{
    int x = 5;
    int* y = malloc(sizeof(int));
    *y = 6;

    printf("main: %p\n", main);
    printf("msg: %p\n", msg);
    printf("stack object: %p\n", &x);
    printf("heap object: %p\n", y);

    free(y);
    return 0;
}
