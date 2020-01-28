// This program:
//  - Opens "msg.txt"
//  - Reads it and counts the lines (= "\n" characters)
//  - Prints it
//  - Does all IO with syscalls rather than stdlib functions.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int
main(int argc, char* argv)
{
    char in_buf[192];
    char out_buf[64];
    long fd = open("msg.txt", O_RDONLY);

    long count = read(fd, in_buf, 192);

    long lines = 0;
    for(long ii = 0; ii < count; ++ii) {
        if (in_buf[ii] == '\n') {
            lines += 1;
        }
    }

    count = sprintf(out_buf, "msg.txt has # of lines: %ld\n", lines);

    write(1, out_buf, count);

    close(fd);
    return 0;
}
