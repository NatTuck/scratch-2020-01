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

    if ((cpid = fork())) {
        int st;
        wait(&st);
    }
    else {
        execlp("echo", "echo", "In", "subprocess", NULL);
        // Exec syscall wrappers:
        //  All start with "exec"
        //  Then argv format:
        //    "l" means "list" means the args are directly in the call.
        //    "v" means "vector" means the args are in a separate array.
        //    "p" mean we use $PATH to find executables.
    }

    printf("All done\n");

    return 0;
}
