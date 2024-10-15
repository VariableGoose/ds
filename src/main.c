#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

static void print_set(const HashSet(int) set) {
    printf("{");
    size_t j = 0;
    for (HashSetIter i = hash_set_iter_new(set);
            hash_set_iter_valid(set, i);
            i = hash_set_iter_next(set, i)) {
        printf("%d", set[i]);
        if (j < hash_set_count(set) - 1) {
            printf(", ");
        }
        j++;
    }
    printf("}\n");
}

int main(void) {
    HashSet(int) a = NULL;
    for (int i = 0; i < 10; i++) {
        hash_set_insert(a, i);
    }
    hash_set_insert(a, 0);
    printf("a: ");
    print_set(a);

    HashSet(int) b = NULL;
    for (int i = 3; i < 7; i++) {
        hash_set_insert(b, i);
    }
    printf("b: ");
    print_set(b);

    HashSet(int) unionn = hash_set_union(a, b);
    printf("union: ");
    print_set(unionn);
    hash_set_free(unionn);

    HashSet(int) intersect = hash_set_intersect(a, b);
    printf("intersect: ");
    print_set(intersect);
    hash_set_free(intersect);

    HashSet(int) diff = hash_set_difference(a, b);
    printf("difference: ");
    print_set(diff);
    hash_set_free(diff);

    hash_set_free(a);
    hash_set_free(b);

    return 0;
}
