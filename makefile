CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic

sudoku_solver: main.c sudoku.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test