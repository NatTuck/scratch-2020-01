#include <stdlib.h>
#include <string.h>

#include "map.h"

pair*
make_pair(const char* key, const char* val, pair* next)
{
    // This is broken, see the 3650a version for working.

    pair* pp = malloc(sizeof(pair));
    pp->key = strdup(key);
    pp->val = strdup(val);
    pp->next = next;
    return pp;
}

void
free_pair(pair* pp)
{
    if (pp) {
        // free strings
        free_pair(pp->next);
        free(pp);
    }
}

map*
make_map()
{
    map* mm = malloc(sizeof(map));
    mm->size = 0;
    mm->capacity = 4;
    mm->data = calloc(mm->capacity, sizeof(pair*));
    return mm;
}

void
free_map(map* mm)
{
    for (long ii = 0; ii < mm->capacity; ++ii) {
        if(mm->data[ii]) {
            free_pair(mm->data[ii]);
        }
    }
    free(mm->data);
    free(mm);
}

long
hash(const char* text)
{
    long hh = 0;
    for (long ii = 0; text[ii]; ++ii) {
        hh = hh * 67 + text[ii];
    }
    return hh;
}

void
map_grow(map* mm)
{
    long nn = mm->capacity;
    pair** data = mm->data;

    mm->capacity = 2 * nn;
    mm->data = calloc(mm->capacity, sizeof(pair*));
    mm->size = 0;

    for (long ii = 0; ii < nn; ++ii) {
        for (pair* curr = data[ii]; curr; curr->next) {
            map_put(mm, curr->key, curr->val);
        }
        free_pair(data[ii]);
    }
    free(data);
}

void
map_put(map* mm, const char* key, const char* val)
{
    if (mm->size >= mm->capacity) {
        map_grow(mm);
    }

    //long ii = hash(key) % mm->capacity;
    long ii = hash(key) & (mm->capacity - 1);
    mm->data[ii] = make_pair(key, val, mm->data[ii]);
    mm->size += 1;
}

char*
map_get(map* mm, const char* key)
{
    long ii = hash(key) & (mm->capacity - 1);

    for (pair* curr = mm->data[ii]; curr; curr->next) {
        if (strcmp(key, curr->key) == 0) {
            return curr->val;
        }
    }
    return 0;
}
