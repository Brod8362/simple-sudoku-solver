#include "sudoku.h"
#include <stdio.h>

int main(void) {
    sudoku_board board;
    load_from(&board, 0);
    sudoku_board solved;

    printf("INPUT BOARD:\n");
    print_board(&board, 0);

    algorithm_params params;
    params_init(&params, 20);

    if (try_solve(&board, &solved, &params)) {
        if (board_solved(&solved)) {
            printf("SOLVED BOARD (%d steps):\n", params.iterations_used);
        } else {
            printf("\033[1;31mAlgorithm says solved, but board isn't actually solved.\033[0m\n");
        }
        print_board(&solved, 0);
    }  else {
        printf("Couldn't solve.\n");
    }
}