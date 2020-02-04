#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

int
main(int _ac, char* _av[])
{
    map* noises = make_map();
    map_put(noises, "cow", "moo");
    map_put(noises, "elephant", "you never call");
    char* text = strdup("hi");
    map_put(noises, "person", text);

    printf("The cow says: %s\n", map_get(noises, "cow"));
    free(text);

    printf("The person says: %s\n", map_get(noises, "hi"));
   
    free_map(noises);
    return 0;
}
