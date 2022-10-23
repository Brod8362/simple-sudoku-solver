#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sudoku.h"


int try_solve(sudoku_board* init, sudoku_board* solution) {
    
}

int legal(sudoku_board* board, size_t idx, int is_row) {
    char encountered[9];
    memset(encountered, 0, 9*sizeof(char));
    for (size_t pos = 0; pos < 9; pos++) {
        char index = (is_row ? board->board[pos][idx] : board->board[idx][pos])-1;
        if (encountered[index] == 0) {
            encountered[index]++;
        } else {
            return 0;
        }
    }
    return 1;
}

int row_legal(sudoku_board* board, size_t row) {
    return legal(board, row, 1);
}

int col_legal(sudoku_board* board, size_t col) {
    return legal(board, col, 0);
}

int segment_legal(sudoku_board* board, size_t segment_x, size_t segment_y) {
    const size_t segment_left = (segment_x * 3);
    const size_t segment_top = (segment_y * 3);
    char encountered[9];
    memset(encountered, 0, 9*sizeof(char));
    for (size_t i = segment_left; i < segment_left + 3; i++) {
        for (size_t j = segment_top; j < segment_top + 3; j++) {
            char index = board->board[i][j]-1;
            if (encountered[index] == 0) {
                encountered[index]++;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

void print_board(sudoku_board* board, int highlight_mode) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board->board[i][j]);
            if (j == 2 || j == 5) {
                printf("| ");
            }
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("=====================\n");
        }
    }
}

void board_init(sudoku_board* board) {
    for (int i = 0; i < 9; i++) {
        memset(board->board[i], 0, 9);
    }
}

