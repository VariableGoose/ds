#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

int main(void) {
    HashMap(int, int) map = NULL;

    hash_map_insert(map, 3, 42);
    int value = hash_map_get(map, 3);
    printf("%d\n", value); // Output: 42

    hash_map_set(map, 3, 83);
    value = hash_map_get(map, 3);
    printf("%d\n", value); // Output: 83

    hash_map_remove(map, 3);
    printf("%d\n", value); // Output: 0

    hash_map_free(map);

    return 0;
}
