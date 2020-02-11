#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int _ac, char* _av[])
{
    int cpid;

    if ((cpid = fork())) {
        wait(0);
        printf("After running echo.\n");
    }
    else {
        int fd = open("stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
        close(1);
        dup(fd);
        close(fd);

        execlp("echo", "echo", "child", "says", "hi", NULL);
    }

    return 0;
}
