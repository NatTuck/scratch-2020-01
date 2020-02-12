#include <stdio.h>
#include <unistd.h>

int
main(int _ac, char* _av[])
{
    char* msg = "hello";
    write(1, msg, 5);
    while(1);
    return 0;
}
