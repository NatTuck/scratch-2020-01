#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void
check_rv(int rv)
{
    if (rv < 0) {
        perror("fail");
        exit(1);
    }
}

int
main(int _ac, char* _av[])
{
    int rv;
    char msg[] = "Hello, pipe.\n";

    int pipe_fds[2];
    rv = pipe(pipe_fds);
    check_rv(rv);

    int p_read  = pipe_fds[0];
    int p_write = pipe_fds[1];

    int cpid;
    if ((cpid = fork())) {
        close(p_write);

        char temp[100];

        rv = 1;
        while (rv) {
            rv = read(p_read, temp, 99);
            check_rv(rv);
            temp[rv] = 0;
            printf("%s", temp);
        }

        printf("\nall done\n");

        int st;
        waitpid(cpid, &st, 0);
    }
    else {
        close(p_read);

        for (int ii = 0; ii < 12; ++ii) {
            rv = write(p_write, msg, strlen(msg));
            check_rv(rv);
        }

        printf("child process done\n");
    }

    return 0;
}
