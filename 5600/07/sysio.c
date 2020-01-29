#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int _ac, char* _av[])
{
    int thing1 = open("/tmp/thing2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    char* msg = "Hello, Syscalls\n";
    write(thing1, msg, strlen(msg));
    close(thing1);

    char temp[80];
    int thing2 = open("/tmp/thing2.txt", O_RDONLY);
    int len = read(thing2, temp, 79);
    close(thing2);

    temp[len] = 0;

    write(1, temp, strlen(temp));

    return 0;
}
