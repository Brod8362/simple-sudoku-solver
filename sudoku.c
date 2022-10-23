#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "sudoku.h"

#define IS_DIGIT(c) ((c >= '0' && c <= '9'))

int try_solve(sudoku_board* init, sudoku_board* solution) {
    // [col][row][number]
    char working_board[9][9][9];
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            
        }
    }
    return 0;
}

int legal(sudoku_board* board, size_t idx, int is_row, int check_solved) {
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

int row_legal(sudoku_board* board, size_t row) {
    return legal(board, row, 1, 0);
}

int col_legal(sudoku_board* board, size_t col) {
    return legal(board, col, 0, 0);
}

int segment_legal(sudoku_board* board, size_t segment_x, size_t segment_y, int check_solved) {
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

void print_board(sudoku_board* board, int highlight_mode) {
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

void possible_values(sudoku_board* board, char* possiblity_matrix, int x, int y) {
    char value = board->board[y][x];
    if (board->board[y][x] != 0) {

    }
}