#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int _ac, char* _av[])
{
    int opid = getpid();
    int opar = getppid();
    int cpid;

    printf("Hi, I'm %d, child of %d\n", opid, opar);

    if ((cpid = fork())) {
        int pid1 = getpid();
        int par1 = getppid();
        printf("Hi, I'm %d, child of %d (cpid = %d)\n", pid1, par1, cpid);

        int st;
        wait(&st);
    }
    else {
        int pid2 = getpid();
        int par2 = getppid();
        printf("Hi, I'm %d, child of %d (cpid = %d)\n", pid2, par2, cpid);
    }

    printf("All done\n");

    return 0;
}
