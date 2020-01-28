// Open a file called "msg.txt"
// Read the data in it, counting the number of lines (= "\n" characters).
// Print out the count.
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char* argv[])
{
    char in_buf[192];
    char out_buf[64];

    int fd = open("msg.txt", O_RDONLY);
    /*
    if (fd == -1) {
        perror("open failed");
    }

    printf("fd = %d\n", fd);
    */
    long count = read(fd, in_buf, 192);

    long lines = 0;
    for (long ii = 0; ii < count; ++ii) {
        if (in_buf[ii] == '\n') {
            lines += 1;
        }
    }

    count = sprintf(out_buf, "Lines in msg.txt: %ld\n", lines);
    write(1, out_buf, count);

    close(fd);
    return 0;
}
