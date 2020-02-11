#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int _ac, char* _av[])
{
    int opid = getpid();
    int opar = getppid();
    int cpid, pid, par;

    printf("Hi, I'm %d, child of %d.\n", opid, opar);

    if ((cpid = fork())) {
        // in parent
        int st;
        wait(&st);
    }
    else {
        // in child

        execlp("echo", "echo", "this", "is", "echo", NULL);
        // l: take argv as arguments directly
        // p: use PATH environment variable to find program
        //
        // Exec never returns.
        // It just completely wipes out the current process,
        // and makes it the echo program.
    }

    printf("All done.\n");

    return 0;
}
