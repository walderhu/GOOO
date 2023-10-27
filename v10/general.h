#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int menu;
    int game;
    int tmp;
} GAME_t;

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
#define MENU -1

// #define AGAIN 1
#define CONTINUE_GAME 1
#define START_OVER 2
#define EXIT_TO_LOBBY 3
#define EXIT_THE_GAME 4

#define ONGOING 0 // мб убрать
#define X_WON 1
#define O_WON 2
#define NOBODY 3 // мб убрать

#define TRUE 1
#define FALSE 0                          // мб убрать
int lobby(char **board, GAME_t *status); // начальное лобби игры
void draw_board(char **board, GAME_t *status);
void won(char **board, GAME_t status);
int input(char **board, GAME_t *status);
// для реализации pvp
char **table(int);
void initialize_board(char **board);
int input_pvp(char **board);
int check_game_state(char **board);

// доп реализация для pve
int input_pve(char **board);
int minimax(char **board, char player, int depth, int *best_move);
void apply_move(char **board, int move, char player);
void get_moves(char **board, int *moves, int *num_moves);
int evaluate(char **board);
void undo_move(char **board, int move);
// test
int menu();
#endif