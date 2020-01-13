#include <stdio.h>

// Takes a string as the first command line argument.
// If every character in that string is a '5', print "all fives".
// Else, print "not all fives".

int
all_match(char* text, char cc)
{
    for (long ii = 0; text[ii] != 0; ++ii) {
        if (text[ii] != cc) {
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        puts("Usage: ./fives arg");
        return 1;
    }

    if (all_match(argv[1], '5')) {
        puts("all fives");
    }
    else {
        puts("not all fives");
    }

    return 0;
}
