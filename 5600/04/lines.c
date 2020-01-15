// for open(2)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// for close(2) and read(2) and write(2)
#include <unistd.h>

// for non-syscall use only
#include <stdio.h>
#include <string.h>

// Lines.c:
//
//  - open a file named "msg.txt"
//  - count the number of lines in it (== # of '\n')
//  - print out that result
//
// No indirect system calls through the standard C library.


int
main(int _ac, char* _av[])
{
    char read_buf[192];
    char print_buf[64];

    char* intro = "Lines in msg.txt:\n";
    write(1, intro, strlen(intro));

    int fd = open("msg.txt", O_RDONLY);
    long size = read(fd, read_buf, 192);
    long lines = 0;
    for (long ii = 0; ii < size; ++ii) {
        if (read_buf[ii] == '\n') {
            lines += 1;
        }
    }
    close(fd);

    sprintf(print_buf, "lines = %ld\n", lines);
    write(1, print_buf, strlen(print_buf));

    return 0;
}
