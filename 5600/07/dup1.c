#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int _ac, char *_av[])
{
    int cpid;

    if ((cpid = fork())) {
        // parent
        waitpid(cpid, 0, 0);
        printf("%d: Child done\n", getpid());
    }
    else {
        // child
        int fd = open("stdout.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
        close(1);
        dup(fd);
        close(fd);

        execlp("echo", "echo", "this is from echo", NULL);
        abort();
    }

    return 0;
}
