#include "sudoku.h"
#include <stdio.h>

int main(int argc, char** argv) {
    sudoku_board board;
    board_init(&board);
    load_from(&board, 0);
    print_board(&board, 0);
}