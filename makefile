CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

sudoku_solver: main.c sudoku.c
	$(CC) $(CFLAGS) $^ -o $@

test:
	printf "not used"

.PHONY: test