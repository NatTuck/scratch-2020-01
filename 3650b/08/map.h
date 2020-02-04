#ifndef MAP_H
#define MAP_H

typedef struct pair {
    char* key;
    char* val;
    struct pair* next;
} pair;

typedef struct map {
    pair** data;
    long size;
    long capacity;
} map;

map* make_map();
void free_map(map* mm);

void map_put(map* mm, const char* key, const char* val);
char* map_get(map* mm, const char* key);

#endif
