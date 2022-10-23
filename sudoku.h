#ifndef SUDOKU_H
#define SUDOKU_H

#define H_BAD_ROWS 1
#define H_BAD_COLS 2
#define H_BAD_SEGMENTS 4

typedef struct sudoku_board {
    char board[9][9];
} sudoku_board;

typedef struct algorithm_params {
    int success;
    int iterations;
    int iterations_used;
} algorithm_params;

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
 * @param params Struct to store algorithm parameters and result 
 * @return int 1 on success, 0 otherwise.
 */
int try_solve(const sudoku_board* init, sudoku_board* solution, algorithm_params* params);

/**
 * @brief Print a board to stdout.
 * 
 * @param board 
 */
void print_board(const sudoku_board* board, int highlight_mode);

/**
 * @brief Load a board form the given file descriptor.
 * The board will be loaded top left to bottom right. Characters that aren't digits or '-' will be ignored.
 * 0 and '-' are treated as an empty space.
 * @param board 
 * @param fd 
 * @return int 
 */
int load_from(sudoku_board* board, int fd);

/**
 * @brief Copy a sudoku board from src to dst
 * 
 * @param dst Destination board
 * @param src Source board
 */
void sudoku_copy(sudoku_board* dst, const sudoku_board* src);

/**
 * @brief Check if a given board is solved or not.
 * 
 * @param board 
 * @return int 
 */
int board_solved(const sudoku_board* board);

void params_init(algorithm_params* params, int iterations);

#endif