#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int _ac, char* _av[])
{
    int opid = getpid();
    int opar = getppid();
    int cpid;

    printf("Hi, I'm %d, child of %d\n", opid, opar);

    if ((cpid = fork())) {
        // parent process
        int pid1 = getpid();
        int par1 = getppid();
        printf("Hallo, I'm %d, child of %d\n", pid1, par1);

        int st;
        waitpid(cpid, &st, 0);
        printf("Child exited with:\n");
        printf(" wait returned: %d\n", st);
        printf(" WEXITSTATUS(st): %d\n", WEXITSTATUS(st));
    }
    else {
        // child process
        int pid2 = getpid();
        int par2 = getppid();
        printf("Hai, I'm %d, child of %d\n", pid2, par2);

        execlp("echo", "echo", "this is from exec echo", NULL);
        // Exec doesn't return on success.

        printf("After exec.\n");
        exit(1);
    }

    printf("All done\n");

    return 0;
}
