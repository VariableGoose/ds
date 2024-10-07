# Generic Data Structures written in C

A generic implementation of common data structures to make programming in C a little bit nicer with less setup.

## Implemented data structures:
- Vector
- HashSet
- HashMap

## TODO:
- [x] Vector
- [x] HashSet
- [x] HashMap
- [ ] Documentation
- [ ] Examples

## Documentation

### Hash Map
```c
// !!! DON'T DO THIS !!!
// This will save the address to the string on the stack into the hash map
// making the key-value pair invalid.
char stack_string[] = "foo";
hash_map_insert(map, stack_string, 42);

// This is fine since the static string will always be present within
// memory.
hash_map_insert(map, "foo", 42);

// This is also fine, just remember to free the memory when removing the
// key-value pair. This could be thought of as the hash map owning the
// allocated string.
char *heap_string = malloc(4);
strncpy(heap_string, "foo", 3);
hash_map_insert(map, heap_string, 42);
// ...
HashMapIter i = hash_map_remove(map, "foo");
free((void *) map[i].key);

// Using strings on the stack is fine when doign get operations since they're
// not saved anywhere in the hash map. They're only used to match to within
// the hash map.
int foo = 42;
char key[5] = {0};
snprintf(key, 5, "foo%d", foo);
int value = hash_map_get(map, key);
```
