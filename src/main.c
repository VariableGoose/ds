#include <assert.h>
#include <stdio.h>
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
    // printf("%s, %s\n", *_a, *_b);
    return strcmp(*_a, *_b);
}

int main(void) {
    HashMap(const char *, int) map = NULL;
    HashMapDesc desc = hash_map_desc_default(map);
    desc.hash = hash_string;
    desc.cmp = cmp_string;
    hash_map_new(map, desc);

    printf("main bucket_size: %zu\n", sizeof(*map));

    for (size_t i = 0; i < 256; i++) {
        char *str = malloc(8);
        snprintf(str, 8, "id-%zu", i);
        hash_map_insert(map, str, i);
    }

    for (size_t i = 0; i < 256; i += 2) {
        char str[8];
        snprintf(str, 8, "id-%zu", i);
        hash_map_remove(map, str);
    }

    int life = hash_map_get(map, "id-233");
    printf("%d\n", life);

    printf("%zu\n", hash_map_count(map));

    for (HashMapIter iter = hash_map_iter_new(map);
        hash_map_iter_valid(map, iter);
        iter = hash_map_iter_next(map, iter)) {
        printf("%s: %d\n", map[iter].key, map[iter].value);
    }

    hash_map_free(map);

    return 0;
}
