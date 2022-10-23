#ifndef SUDOKU_H
#define SUDOKU_H

#define H_BAD_ROWS 1
#define H_BAD_COLS 2
#define H_BAD_SEGMENTS 4

typedef struct sudoku_board {
    char board[9][9];
} sudoku_board;

/**
 * @brief Initialize a board to all zeroes.
 * 
 * @param board 
 */
void board_init(sudoku_board* board);

/**
 * @brief Attempt to solve the sudoku board.
 * 
 * @param init Initial board.
 * @param solution Pointer to a board to store the solution into.
 * @return int 0 on success, 1 otherwise.
 */
int try_solve(sudoku_board* init, sudoku_board* solution);

/**
 * @brief Print a board to stdout.
 * 
 * @param board 
 */
void print_board(sudoku_board* board, int highlight_mode);


#endif