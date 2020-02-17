#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void
assert_ok(long rv, char* call)
{
    if (rv == -1) {
        fprintf(stderr, "Failed call: %s\n", call);
        perror("error");
        abort();
    }
}

int
main(int _ac, char* _av[])
{
    int* shared = mmap(0, 4096, PROT_READ|PROT_WRITE,
                       MAP_SHARED|MAP_ANONYMOUS, -1, 0);
//    int* shared = mmap(0, 4096, PROT_READ|PROT_WRITE,
//                       MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    assert_ok((long) shared, "mmap");

    for (int ii = 0; ii < 10; ++ii) {
        shared[ii] = ii;
    }

    int cpid;
    if ((cpid = fork())) {
        // parent
        printf("Parent: sleep 1\n");
        //sleep(1);

        printf("Parent: mutating array\n");
        for (int ii = 0; ii < 10; ++ii) {
            shared[ii] = ii * 100;
            sleep(1);
        }

        waitpid(cpid, 0, 0);
    }
    else {
        printf("child: array content\n");
        for (int ii = 0; ii < 10; ++ii) {
            printf("%d ", shared[ii]);
        }
        printf("\n");

        //sleep(2);

        printf("child: array content\n");
        for (int ii = 10; ii >= 0; --ii) {
            printf("%d ", shared[ii]);
            sleep(1);
        }
        printf("\n");
    }

    return 0;
}
