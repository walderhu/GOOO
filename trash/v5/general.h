#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include <stdio.h>
#include <stdlib.h>
#define CREATE 0
#define DELETE 1
#define AI_WIN 1
#define HUMAN_WIN -1
#define DRAW 0
#define BOARD_SIZE 3
#define EMPTY_SPACE ' '
#define PVP 1
#define PVE 2
#define EXIT -1
typedef enum
{
    ONGOING,
    X_WON,
    O_WON,
    NOBODY,
} GameState;
int lobby(); // начальное лобби игры
void draw_board(char **board);
void won(char **board, int PVP_PVE);
void game();
// для реализации pvp
void start_pvp();
char **creat_del_board(int);
void initialize_board(char **board);
int input(char **board);
GameState check_game_state(char **board);

// доп реализация для pve
void start_pve();
int input_pve(char **board);
int minimax(char **board, char player, int depth, int *best_move);
void apply_move(char **board, int move, char player);
void get_moves(char **board, int *moves, int *num_moves);
int evaluate(char **board);
void undo_move(char **board, int move);
#endif