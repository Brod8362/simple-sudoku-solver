#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "sudoku.h"

#define IS_DIGIT(c) ((c >= '0' && c <= '9'))

int try_solve(const sudoku_board* init, sudoku_board* solution, int depth) {
    sudoku_board work;
    board_init(&work);
    if (depth <= 0) {
        return 0;
    }
    if (try_solve_inner(init, &work)) {
        sudoku_copy(solution, &work);
        return 1;
    } else {
        return try_solve(&work, solution, depth-1);
    }
}

int try_solve_inner(const sudoku_board* init, sudoku_board* solution) {
    // [col][row][number]
    char working_board[9][9][9];
    int solved = 1;
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (possible_values(init, working_board[i][j], i, j) == 1) {
                //only one value is possible. put it into the solution matrix.
                for (int z = 0; z < 9; z++) {
                    if (working_board[i][j][z]) {
                        solution->board[i][j] = z+1;
                        break;
                    }
                }
            } else {
                solved = 0;
                //more than one value is possible.
            }
        }
    }
    return solved;
}

int legal(const sudoku_board* board, size_t idx, int is_row, int check_solved) {
    char encountered[9];
    memset(encountered, 0, 9*sizeof(char));
    for (size_t pos = 0; pos < 9; pos++) {
        int index = (is_row ? board->board[idx][pos] : board->board[pos][idx])-1;
        if (index != -1) { //will be -1 for empty spaces
            if (encountered[index] == 0) {
                encountered[index]++;
            } else {
                return 0;
            }
        }
    }
    if (check_solved) {
        for (size_t pos = 0; pos < 9; pos++) {
            if (encountered[pos] != 1) {
                return 0;
            }
        }
        return 1;
    } 
    return 1;
}

int row_legal(const sudoku_board* board, size_t row) {
    return legal(board, row, 1, 0);
}

int col_legal(const sudoku_board* board, size_t col) {
    return legal(board, col, 0, 0);
}

int segment_legal(const sudoku_board* board, size_t segment_x, size_t segment_y, int check_solved) {
    const size_t segment_left = (segment_x * 3);
    const size_t segment_top = (segment_y * 3);
    char encountered[9];
    memset(encountered, 0, 9*sizeof(char));
    for (size_t i = segment_left; i < segment_left + 3; i++) {
        for (size_t j = segment_top; j < segment_top + 3; j++) {
            int index = board->board[i][j]-1;
            if (index != -1) {
                if (encountered[index] == 0) {
                    encountered[index]++;
                } else {
                    return 0;
                }
            }
        }
    }
    if (check_solved) {
        for (size_t pos = 0; pos < 9; pos++) {
            if (encountered[pos] != 1) {
                return 0;
            }
        }
        return 1;
    }
    return 1;
}

void print_board(const sudoku_board* board, int highlight_mode) {
    printf("┏━━━━━━━┳━━━━━━━┳━━━━━━━┓\n");
    for (int i = 0; i < 9; i++) {
        printf("┃ ");
        for (int j = 0; j < 9; j++) {
            int value = board->board[i][j];
            if (value == 0) {
                printf("- ");
            } else {
                printf("%d ", value);
            }
            if (j == 2 || j == 5) {
                printf("┃ ");
            }
        }
        printf("┃\n");
        if (i == 2 || i == 5) {
            printf("┠━━━━━━━╂━━━━━━━╂━━━━━━━┨\n");
        }
    }
    printf("┗━━━━━━━┻━━━━━━━┻━━━━━━━┛\n");
}

void board_init(sudoku_board* board) {
    for (int i = 0; i < 9; i++) {
        memset(board->board[i], 0, 9);
    }
}

int load_from(sudoku_board* board, int fd) {
    int x_pos = 0, y_pos = 0;
    char c;
    while (y_pos < 9 && read(fd, &c, 1)) {
        if (IS_DIGIT(c) || c == '-') {
            if (c == '-') {
                board->board[y_pos][x_pos] = 0;
            } else {
                board->board[y_pos][x_pos] = c - '0';
            }
            
            if (x_pos == 8) {
                y_pos++;
                x_pos = 0;
            } else {
                x_pos++;
            }
        }
    }
    return (y_pos == 9);
}

int possible_values(const sudoku_board* board, char* possiblity_matrix, const size_t y, const size_t x) {
    const int value = board->board[y][x];
    if (value == 0) {
        memset(possiblity_matrix, 1, 9); //all values are possible until otherwise found in use.
        for (size_t row = 0; row < 9; row++) { //check the horizontal values around point
            if (row != x) {
                int r_value = board->board[y][row];
                possiblity_matrix[r_value-1] = 0;
            }
        }

        for (size_t col = 0; col < 9; col++) { //check the vertical values around point
            if (col != y) {
                const int r_value = board->board[col][x];
                possiblity_matrix[r_value-1] = 0;
            }
        }

        const size_t s_top = (y/3)*3;
        const size_t s_left = (x/3)*3;

        for (size_t r = s_left; r < s_left+3; r++) {
            for (size_t c = s_top; c < s_top+3; c++) {
                const int r_value = board->board[c][r];
                possiblity_matrix[r_value-1] = 0;
            }
        }
        
        int num_possible = 0;
        for (size_t v = 0; v < 9; v++) {
            if (possiblity_matrix[v]) num_possible++;
        }
        return num_possible;
    } else {
        memset(possiblity_matrix, 0, 9);
        possiblity_matrix[value-1] = 1;
        return 1;
    }
}

void sudoku_copy(sudoku_board* dst, const sudoku_board* src) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            dst->board[i][j] = src->board[i][j];
        }
    }
}

int board_solved(const sudoku_board* board) {
    for (int i = 0; i < 9; i++) {
        if (!legal(board, i, 0, 1) || !legal(board, i, 1, 1)) {
            return 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!segment_legal(board, i, j, 1)) {
                return 0;
            }
        }
    }
    return 1;
}