
#include <stdio.h>

#include "list.h"
#include "tokenize.h"
#include "ast.h"
#include "parse.h"

int
main(int _ac, char* _av[])
{
    char line[100];

    while (1) {
        char* rv = fgets(line, 96, stdin);
        if (!rv) {
            break;
        }

        list* toks = tokenize(line);
        print_list(toks);

        calc_ast* ast = parse(toks);
        print_ast(ast);

        //printf(" = %d\n", ast_eval(ast));
        /*
        free_ast(ast);
        free_list(toks);
        */
    }

    return 0;
}
