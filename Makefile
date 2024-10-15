CC := clang
CFLAGS := -std=c99 -Wall -Wextra -ggdb
IFLAGS := -Iinclude

SRC := src/ds.c

main:
	@mkdir -p bin
	$(CC) $(CFLAGS) -o bin/main src/main.c src/ds.c $(IFLAGS)
