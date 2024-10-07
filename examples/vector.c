#include <stdio.h>

#include "ds.h"

int main(void) {
    Vec(int) vec = NULL;

    vec_push(vec, 4);
    vec_push(vec, 2);

    vec_free(vec);

    return 0;
}
