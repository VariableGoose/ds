#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

// static void print_set(const HashSet(int) set) {
//     printf("{");
//     size_t j = 0;
//     for (HashSetIter i = hash_set_iter_new(set);
//             hash_set_iter_valid(set, i);
//             i = hash_set_iter_next(set, i)) {
//         printf("%d", set[i]);
//         if (j < hash_set_count(set) - 1) {
//             printf(", ");
//         }
//         j++;
//     }
//     printf("}\n");
// }

int main(void) {
    HashMap(int, int) map = NULL;

    for (int i = 0; i < 128; i++) {
        hash_map_insert(map, i, 1);
    }

    hash_map_free(map);

    return 0;
}
