#include "sudoku.h"

int main(int argc, char** argv) {
    sudoku_board board;
    board_init(&board);
    print_board(&board, 0);
}