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
        waitpid(cpid, 0, 0);
        printf("%d: child done\n", getpid());
    }
    else {
        int fd = open("stdout.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
        close(1);
        dup(fd);
        close(fd);

        execlp("echo", "echo", "executed", "echo", NULL);
    }

    return 0;
}
