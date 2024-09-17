#include "ds.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

//
// Utils
//

size_t fvn1a_hash(const void *data, size_t len) {
    const char *_data = data;
    size_t hash = 2166136261u;
    for (size_t i = 0; i < len; i++) {
        hash ^= *(_data + i);
        hash *= 16777619;
    }
    return hash;
}

//
// Vector
//

#define INITIAL_CAPACITY 8

typedef struct VecHeader VecHeader;
struct VecHeader {
    size_t item_size;
    size_t capacity;
    size_t len;
};

#define vec_to_header(vec) ((VecHeader*) ((uint8_t*) (vec) - sizeof(VecHeader)))
#define header_to_vec(header) ((void*) ((uint8_t*) (header) + sizeof(VecHeader)))

size_t vec_len(const void* vec) {
    if (vec == NULL) {
        return 0;
    }

    return vec_to_header(vec)->len;
}

size_t vec_capacity(const void* vec) {
    if (vec == NULL) {
        return 0;
    }

    return vec_to_header(vec)->capacity;
}

void _vec_create(void** vec, size_t item_size) {
    if (*vec != NULL) {
        return;
    }

    VecHeader *header = malloc(sizeof(VecHeader) + item_size*INITIAL_CAPACITY);
    *header = (VecHeader) {
        .item_size = item_size,
        .capacity = INITIAL_CAPACITY,
    };

    *vec = header_to_vec(header);
}

void _vec_free(void** vec) {
    if (*vec == NULL) {
        return;
    }

    free(vec_to_header(*vec));

    *vec = NULL;
}

static void ensure_capacity(void** vec, size_t len) {
    VecHeader *header = vec_to_header(*vec);
    if (header->capacity >= header->len + len) {
        return;
    }

    while (header->len + len > header->capacity) {
        header->capacity *= 2;
    }

    header = realloc(header, sizeof(VecHeader) + header->item_size*header->capacity);
    if (header == NULL) {
        *vec = NULL;
        return;
    }
    *vec = header_to_vec(header);
}

void _vec_insert_arr(void** vec, size_t index, const void* arr, size_t len) {
    VecHeader *header = vec_to_header(*vec);
    assert(index <= header->len);
    ensure_capacity(vec, len);
    header = vec_to_header(*vec);

    void *end = (*vec) + (index+len)*header->item_size;
    void *dest = (*vec) + index*header->item_size;

    memmove(end, dest, (header->len - index)*header->item_size);
    memcpy(dest, arr, len*header->item_size);

    header->len += len;
}

void _vec_remove_arr(void** vec, size_t index, size_t len, void *result) {
    VecHeader *header = vec_to_header(*vec);
    assert(index+len <= header->len);

    void *end = (*vec) + (index+len)*header->item_size;
    void *dest = (*vec) + index*header->item_size;

    if (result != NULL) {
        memcpy(result, dest, len*header->item_size);
    }
    memmove(dest, end, (header->len - index - len)*header->item_size);

    header->len -= len;
}

void _vec_insert_fast(void** vec, size_t index, const void* element) {
    VecHeader *header = vec_to_header(*vec);
    assert(index <= header->len);
    ensure_capacity(vec, 1);
    header = vec_to_header(*vec);

    void *end = (*vec) + header->len*header->item_size;
    void *dest = (*vec) + index*header->item_size;

    memcpy(end, dest, header->item_size);
    memcpy(dest, element, header->item_size);

    header->len += 1;
}

void _vec_remove_fast(void** vec, size_t index, void *result) {
    VecHeader *header = vec_to_header(*vec);
    assert(index+1 <= header->len);

    void *end = (*vec) + (header->len-1)*header->item_size;
    void *dest = (*vec) + index*header->item_size;

    if (result != NULL) {
        memcpy(result, dest, header->item_size);
    }
    memcpy(dest, end, header->item_size);

    header->len -= 1;
}
