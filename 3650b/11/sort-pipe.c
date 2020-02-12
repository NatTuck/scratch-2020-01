#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

int
main(int _ac, char* _av[])
{
    // The plan
    //   - run "sort sample.txt"
    //   - redirect the output to a pipe
    //   - read the output of the pipe in anohter process
    //   - capitalize all 'e's
    //   - print the resulting text

    int cpid, rv;

    int pipes[2];
    rv = pipe(pipes);
    assert(rv != -1);

    // pipes[0] is for reading
    // pipes[1] is for writing

    if ((cpid = fork())) {
        // parent

    }
    else {
        //close(pipes[0]);
        // child

        rv = close(1);
        assert(rv != -1);

        rv = dup(pipes[1]);
        assert(rv != -1);

        char* args[] = {"sort", "sample.txt", 0};
        execvp("sort", args);
        assert(0);
    }

    char tmp[256];
    int  nn;

    close(pipes[1]);

    do {
        nn = read(pipes[0], tmp, 256);
        assert(nn != -1);

        for (int ii = 0; ii < nn; ++ii) {
            if (tmp[ii] == 'e') {
                tmp[ii] = 'E';
            }
        }

        rv = write(1, tmp, nn);
        assert(rv != -1);
    } while (nn != 0);

    int status;
    waitpid(cpid, &status, 0);

    return 0;
}
