#include <stdio.h>
#include <assert.h>

#include "ds.h"

int main(void) {
    HashSet(int) set = NULL;

    for (int i = 0; i < 128; i++) {
        hash_set_insert(set, i);
    }

    for (size_t i = 0; i < 128; i += 2) {
        hash_set_remove(set, i);
    }

    for (size_t i = 0; i < 128; i++) {
        printf("%d", hash_set_contains(set, i));
    }
    printf("\n");

    hash_set_free(set);

    return 0;
}
