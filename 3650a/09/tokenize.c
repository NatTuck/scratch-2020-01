
// Kinds of tokens:
//  - Numbers (one or more digits)
//  - Operators (not digits)
//
// Whitespace isn't tokens.

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

char*
read_number(const char* text, long ii)
{
    int nn = 0;
    while (isdigit(text[ii + nn])) {
        ++nn;
    }

    char* num = malloc(nn + 1);
    memcpy(num, text + ii, nn);
    num[nn] = 0;
    return num;
}

list*
tokenize(const char* text)
{
    list* xs = 0;

    long nn = strlen(text);
    long ii = 0;
    while (ii < nn) {
        if (isspace(text[ii])) {
            ++ii;
            continue;
        }

        if (isdigit(text[ii])) {
            char* num = read_number(text, ii);
            xs = cons(num, xs);
            ii += strlen(num);
            free(num);
            continue;
        }

        // Else, it must be an operator
        char op[] = "x";
        op[0] = text[ii];
        xs = cons(op, xs);
        ++ii;
    }

    return rev_free(xs);
}
