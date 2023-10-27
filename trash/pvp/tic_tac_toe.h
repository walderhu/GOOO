#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#define BOARD_SIZE 3
#define EMPTY_SPACE ' '

typedef enum {
    ONGOING,
    X_WON,
    O_WON,
    DRAW
} GameState;

char **creat_del_board(int);
void initialize_board(char **board);
void draw_board(char **board);
void input(char ** board);
GameState check_game_state(char **board);
#endif