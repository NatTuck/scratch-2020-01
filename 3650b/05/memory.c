
#include <stdio.h>
#include <stdlib.h>

char* msg = "hello";

int
main(int _ac, char* _av[])
{
    int x = 5;
    int* y = malloc(sizeof(int));
    *y = 7;

    printf("address of main: %p\n", main);
    printf("address of msg: %p\n", msg);
    printf("address of x on stack: %p\n", &x);
    printf("address of y on heap: %p\n", y);

    free(y);
    return 0;
}
