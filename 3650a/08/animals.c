#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"


int
main(int _ac, char* _av[])
{
    map* noises = make_map();
    map_put(noises, "chicken", "bawk");
    map_put(noises, "cow", "moo");
    map_put(noises, "elephant", "toot");
    map_put(noises, "dog", "woof");
    map_put(noises, "cat", "meow");

    char* greeting = strdup("Good morning");
    char* fix = "evening";
    memcpy(greeting + 5, fix, strlen(fix));
    map_put(noises, "nat", greeting);

    printf("The cow says: %s\n", map_get(noises, "cow"));

    free(greeting);

    printf("The nat says: %s\n", map_get(noises, "nat"));

    map_del(noises, "cow");
    printf("After delete, iterate:\n");

    for (map_it it = iterate(noises); has_next(it); it = next(it)) {
        printf("The %s says: %s\n", it.item->key, it.item->val);
    }

    free_map(noises);
    return 0;
}
