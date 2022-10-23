#include "sudoku.h"
#include <stdio.h>

int main(void) {
    sudoku_board board;
    load_from(&board, 0);
    print_board(&board, 0);
}