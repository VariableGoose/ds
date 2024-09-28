#ifndef __DATA_STRUCTURES__
#define __DATA_STRUCTURES__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

//
// Vector
//

#define Vec(T) T *

#define vec_free(vec) _vec_free((void **) &vec)

extern size_t vec_len(const void *vec);
extern size_t vec_capacity(const void *vec);
extern size_t vec_element_size(const void *vec);

#define vec_push(vec, element);
#define vec_pop(vec);

#define vec_insert(vec, index, element);
#define vec_remove(vec, index);

#define vec_insert_fast(vec, index, element);
#define vec_remove_fast(vec, index);

#define vec_insert_arr(vec, index, arr, len);
#define vec_remove_arr(vec, index, len, result);

//
// HashSet
//

typedef struct HashSetDesc HashSetDesc;
struct HashSetDesc {
    size_t element_size;
    size_t (*hash)(const void *, size_t);
    int (*cmp)(const void *, const void *, size_t);
};

#define HashSet(T) T *

#define hash_set_new(desc) _hash_set_new(desc)
#define hash_set_free(set) _hash_set_free((void **) &set)

#define hash_set_insert(set, element)
#define hash_set_remove(set, element)
#define hash_set_contains(set, element)

extern void *hash_set_union(const void *a, const void *b);
extern void *hash_set_intersect(const void *a, const void *b);
extern void *hash_set_difference(const void *a, const void *b);

//
// HashMap
//

typedef struct HashMapDesc HashMapDesc;
struct HashMapDesc {
    size_t key_size;
    size_t value_size;
    const void *zero_value;

    size_t (*hash)(const void *, size_t);
    int (*cmp)(const void *, const void *, size_t);
};
#define hash_map_desc_default(map) (HashMapDesc) { \
    .key_size = sizeof(map->key), \
    .value_size = sizeof(map->value), \
    .hash = fvn1a_hash, \
    .cmp = memcmp, \
}

#define HashMap(TKey, TValue) struct { TKey key; TValue value; } *

#define hash_map_new(map, desc) _hash_map_new((void **) &map, desc);
#define hash_map_free(map) _hash_map_free((void **) &map);

#define hash_map_insert(map, K, V) do { \
    if (map == NULL) { \
        hash_map_new(map, hash_map_desc_default(map)); \
    } \
    __typeof__(map->key) temp_key = K; \
    __typeof__(map->value) temp_value = V; \
    _hash_map_insert((void **) &map, &temp_key, &temp_value); \
} while (0)
#define hash_map_set(map, K, V) do { \
    if (map == NULL) { \
        hash_map_new(map, hash_map_desc_default(map)); \
    } \
    __typeof__(map->key) temp_key = K; \
    __typeof__(map->value) temp_value = V; \
    _hash_map_set((void **) &map, &temp_key, &temp_value); \
} while (0)

#define hash_map_remove(map, K) do { \
    if (map == NULL) { \
        hash_map_new(map, hash_map_desc_default(map)); \
    } \
    __typeof__(map->key) temp_key = K; \
    _hash_map_remove((void **) &map, &temp_key); \
} while (0)

#define hash_map_get(map, K) ({ \
        if (map == NULL) { \
            hash_map_new(map, hash_map_desc_default(map)); \
        } \
        __typeof__(map->value) result; \
        __typeof__(map->key) temp_key = K; \
        _hash_map_get(map, &temp_key, &result); \
        result; \
    })

extern void _hash_map_new(void **map, HashMapDesc desc);
extern void _hash_map_free(void **map);
extern void _hash_map_insert(void **map, const void *key, const void *value);
extern void _hash_map_set(void **map, const void *key, const void *value);
extern void _hash_map_remove(void **map, const void *key);
extern void _hash_map_get(const void *map, const void *key, void *result);
extern size_t hash_map_count(const void *map);

//
// Utils
//

extern size_t fvn1a_hash(const void *data, size_t len);

extern void *hash_set_to_vec(const void *set);
#define vec_to_hash_set(vec)

//
// Private implementation details.
//

//
// Vector
//

#undef vec_push
#undef vec_pop
#undef vec_insert
#undef vec_remove
#undef vec_insert_fast
#undef vec_remove_fast
#undef vec_insert_arr
#undef vec_remove_arr

#define vec_push(vec, element) vec_insert_fast(vec, vec_len(vec), element)
#define vec_pop(vec) vec_remove_fast(vec, vec_len(vec)-1)

#define vec_insert(vec, index, element) ({ \
        if (vec == NULL) { \
            _vec_create((void**) &vec, sizeof(*vec)); \
        } \
        __typeof__(element) temp = element; \
        _vec_insert_arr((void**) &vec, index, &temp, 1); \
    })
#define vec_remove(vec, index) ({ \
        if (vec == NULL) { \
            _vec_create((void**) &vec, sizeof(*vec)); \
        } \
        __typeof__(*vec) result; \
        _vec_remove_arr((void**) &vec, index, 1, &result); \
        result; \
    })

#define vec_insert_fast(vec, index, element) ({ \
        if (vec == NULL) { \
            _vec_create((void**) &vec, sizeof(*vec)); \
        } \
        __typeof__(element) temp = element; \
        _vec_insert_fast((void**) &vec, index, &temp); \
    })
#define vec_remove_fast(vec, index) ({ \
        if (vec == NULL) { \
            _vec_create((void**) &vec, sizeof(*vec)); \
        } \
        __typeof__(*vec) result; \
        _vec_remove_fast((void**) &vec, index, &result); \
        result; \
    })

#define vec_insert_arr(vec, index, arr, len) ({ \
        if (vec == NULL) { \
            _vec_create((void**) &vec, sizeof(*vec)); \
        } \
        _vec_insert_arr((void**) &vec, index, arr, len); \
    })
#define vec_remove_arr(vec, index, len, result) ({ \
        if (vec == NULL) { \
            _vec_create((void**) &vec, sizeof(*vec)); \
        } \
        _vec_remove_arr((void**) &vec, index, len, result); \
    })

extern void _vec_create(void** vec, size_t element_size);
extern void _vec_free(void** vec);
extern void _vec_insert_arr(void** vec, size_t index, const void* arr, size_t len);
extern void _vec_remove_arr(void** vec, size_t index, size_t len, void *result);
extern void _vec_insert_fast(void** vec, size_t index, const void* element);
extern void _vec_remove_fast(void** vec, size_t index, void *result);

//
// HashSet
//

#undef hash_set_insert
#undef hash_set_remove
#undef hash_set_contains

#define _hash_set_desc_default(element_type) (HashSetDesc) {\
    .element_size = sizeof(element_type), \
    .hash = fvn1a_hash, \
    .cmp = memcmp, \
}

#define hash_set_insert(set, element) do { \
    if (set == NULL) { \
        set = hash_set_new(_hash_set_desc_default(*set)); \
    } \
    __typeof__(element) temp = element; \
    _hash_set_insert((void **) &set, &temp); \
} while(0)

#define hash_set_remove(set, element) do { \
    if (set == NULL) { \
        set = hash_set_new(_hash_set_desc_default(*set)); \
    } \
    __typeof__(element) temp = element; \
    _hash_set_remove((void **) &set, &temp); \
} while(0)

#define hash_set_contains(set, element) ({ \
    if (set == NULL) { \
        set = hash_set_new(_hash_set_desc_default(*set)); \
    } \
    __typeof__(element) temp = element; \
    _hash_set_contains(set, &temp); \
})

extern void *_hash_set_new(HashSetDesc desc);
extern void _hash_set_free(void **set);
extern void _hash_set_insert(void **set, const void *element);
extern void _hash_set_remove(void **set, const void *element);
extern bool _hash_set_contains(const void *set, const void *element);

//
// Utils
//

#undef vec_to_hash_set
#define vec_to_hash_set(vec) ({ \
        __typeof__(vec) set = hash_set_new(_hash_set_desc_default(*vec)); \
        _vec_to_hash_set(vec, &set); \
        set; \
    })
extern void _vec_to_hash_set(const void *vec, void **hash_set);

#ifdef __cplusplus
}
#endif

#endif
