#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ds.h"

size_t hash_string(const void *key, size_t size) {
    (void)size;
    char *const *_key = key;
    return fvn1a_hash(*_key, strlen(*_key));
}

int cmp_string(const void *a, const void *b, size_t size) {
    (void)size;
    char *const *_a = a;
    char *const *_b = b;
    return strcmp(*_a, *_b);
}

int main(void) {
    HashMap(const char *, int) map = NULL;
    HashMapDesc desc = hash_map_desc_default(map);
    desc.hash = hash_string;
    desc.cmp = cmp_string;
    hash_map_new(map, desc);

    hash_map_insert(map, "foo", 42);
    int value = hash_map_get(map, "foo");
    printf("foo: %d\n", value);

    hash_map_free(map);

    return 0;
}
