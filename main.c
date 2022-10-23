#include "sudoku.h"
#include <stdio.h>

void example_callback(const sudoku_board* before, const sudoku_board* after, int iteration_number) {
    printf("ITERATION %d\n", iteration_number);
    print_board(before, 0);
    print_board(after, 0);
}

int main(void) {
    sudoku_board board;
    load_from(&board, 0);
    sudoku_board solved;

    printf("INPUT BOARD:\n");
    print_board(&board, 0);

    algorithm_params params;
    params_init(&params, 20);
    params.on_iteration_callback = example_callback;

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