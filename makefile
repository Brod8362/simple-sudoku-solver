CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -O3

sudoku_solver: main.c sudoku.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test