#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

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
    int rv, cpid;

    int pipe_fds[2];
    rv = pipe(pipe_fds);
    check_rv(rv);

    int p_read  = pipe_fds[0];
    int p_write = pipe_fds[1];

    if ((cpid = fork())) {
        close(p_write);

    }
    else {
        close(p_read);

        rv = close(1);
        check_rv(rv);
        rv = dup(p_write);
        check_rv(rv);
        rv = close(p_write);
        check_rv(rv);

        char* args[] = {"sort", "words.txt", 0};
        execvp("sort", args);
        assert(0);
    }

    char tmp[256];
    int nn = 1;;

    do {
        nn = read(p_read, tmp, 256);
        check_rv(nn);

        for (int ii = 0; ii < nn; ++ii) {
            if (tmp[ii] == 'e') {
                tmp[ii] = 'E';
            }
        }

        rv = write(1, tmp, nn);
        check_rv(rv);
    } while (nn != 0);

    int st;
    waitpid(cpid, &st, 0);

    return 0;
}
