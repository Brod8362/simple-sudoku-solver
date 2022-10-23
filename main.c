#include "sudoku.h"
#include <stdio.h>

int main(void) {
    sudoku_board board;
    load_from(&board, 0);
    sudoku_board solved;
    board_init(&solved);

    print_board(&board, 0);

    try_solve(&board, &solved, 20);

    print_board(&solved, 0);

    if(board_solved(&solved)) {
        printf("solved!\n");
    } else {
        printf("not solved...\n");
    }
}