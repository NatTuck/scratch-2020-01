#include <stdio.h>

int
all_match(char* text, char cc)
{
    for (int ii = 0; text[ii]; ++ii) {
        if (text[ii] != cc) {
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char* argv[])
{
    if (all_match(argv[1], '5')) {
        puts("all five");
    }
    else {
        puts("not all five");
    }
    return 0;
}
