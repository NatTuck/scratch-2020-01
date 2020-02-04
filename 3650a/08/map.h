#ifndef MAP_H
#define MAP_H

typedef struct pair {
    char* key;
    char* val;
    struct pair* next;
} pair;

typedef struct map {
    pair** data;
    size_t size;
    size_t capacity;
} map;

typedef struct map_it {
    map* mm;
    size_t ii;
    pair* item;
} map_it;

map* make_map();
void free_map(map* mm);

// Hash map takes ownership of copies of key and val.
void map_put(map* mm, const char* key, const char* val);

// Hash map returns an unowned reference to its copy of the value.
char* map_get(map* mm, const char* key);

void map_del(map* mm, const char* key);

map_it iterate(map* mm);
int    has_next(map_it it);
map_it next(map_it it);

#endif
