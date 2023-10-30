#include "general.h"

int minimax(char *board, char player, int depth, int *best_move)
{
    if (check_game_state(board))
        return evaluate(board);

    int moves[9];
    int num_moves = 0;
    get_moves(board, moves, &num_moves);

    int best_score = (player == 'X') ? -2 : 2;
    int current_move = -1;

    for (int i = 0; i < num_moves; i++)
    {
        int move = moves[i];
        apply_move(board, move, player);
        int score = minimax(board, (player == 'X') ? 'O' : 'X', depth + 1, NULL);
        if ((player == 'X' && score > best_score) || (player == 'O' && score < best_score))
        {
            best_score = score;
            current_move = move;
        }
        undo_move(board, move);
    }

    if (best_move != NULL) // Если указатель best_move не равен NULL, установите его как текущий лучший ход.
        *best_move = current_move;

    return best_score;
}

int evaluate(char *board)
{
    int GameStatus = -1000;
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
        if (board[i * BOARD_SIZE] != EMPTY_SPACE && board[i * BOARD_SIZE] == board[i * BOARD_SIZE + 1] && board[i * BOARD_SIZE + 1] == board[i * BOARD_SIZE + 2])
            GameStatus = (board[i * BOARD_SIZE] == 'X') ? AI_WIN : HUMAN_WIN;
    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++)
        if (board[j] != EMPTY_SPACE && board[j] == board[BOARD_SIZE + j] && board[BOARD_SIZE + j] == board[2 * BOARD_SIZE + j])
            GameStatus = (board[j] == 'X') ? AI_WIN : HUMAN_WIN;
    // Check diagonals
    if (board[0] != EMPTY_SPACE && board[0] == board[BOARD_SIZE + 1] && board[BOARD_SIZE + 1] == board[2 * BOARD_SIZE + 2])
        GameStatus = (board[0] == 'X') ? AI_WIN : HUMAN_WIN;

    if (board[2] != EMPTY_SPACE && board[2] == board[BOARD_SIZE + 1] && board[BOARD_SIZE + 1] == board[2 * BOARD_SIZE])
        GameStatus = (board[2] == 'X') ? AI_WIN : HUMAN_WIN;
    // Check for draw
    if (GameStatus == -1000)
    {
        int num_empty_spaces = 0;
        for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
            if (board[i] == EMPTY_SPACE)
                num_empty_spaces++;
        if (num_empty_spaces == 0)
            GameStatus = DRAW;
    }

    return GameStatus;
}

void get_moves(char *board, int *moves, int *num_moves)
{
    *num_moves = 0;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (board[i] == ' ')
        {
            moves[*num_moves] = i;
            (*num_moves)++;
        }
    }
}

void apply_move(char *board, int move, char player)
{
    board[move] = player;
}

void undo_move(char *board, int move)
{
    board[move] = ' ';
}