#include "sudoku.h"
#include <stdio.h>

void example_callback(const sudoku_board* before, const sudoku_board* after, int iteration_number) {
    printf("ITERATION %d\n", iteration_number);
    printf("\033[31m");
    print_board(before, 0);
    printf("\033[33m");
    print_board(after, 0);
    printf("\033[0m");
}

int main(int argc, char** argv) {
    int debug_print = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0)
            debug_print = 1;
    }
    sudoku_board board;
    load_from(&board, 0);
    sudoku_board solved;

    printf("INPUT BOARD:\n");
    print_board(&board, 0);

    algorithm_params params;
    params_init(&params, 20);
    if (debug_print)
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