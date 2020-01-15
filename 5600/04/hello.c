#include <unistd.h>

int
main(int _ac, char* _av[])
{
    char* msg = "Hello\n";
    write(1, msg, 6);
    return 0;
}
