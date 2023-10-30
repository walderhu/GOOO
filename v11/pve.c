#include "general.h"

int minimax(char **board, char player, int depth, int *best_move)
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

int evaluate(char **board)
{
    int GameStatus = -1000;
    // Проверка строк
    for (int i = 0; i < BOARD_SIZE; i++)
        if (board[i][0] != EMPTY_SPACE && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            GameStatus = (board[i][0] == 'X') ? AI_WIN : HUMAN_WIN;
    // Проверка колонок
    for (int j = 0; j < BOARD_SIZE; j++)
        if (board[0][j] != EMPTY_SPACE && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            GameStatus = (board[0][j] == 'X') ? AI_WIN : HUMAN_WIN;
    // Проверка диагоналей
    if (board[0][0] != EMPTY_SPACE && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        GameStatus = (board[0][0] == 'X') ? AI_WIN : HUMAN_WIN;

    if (board[0][2] != EMPTY_SPACE && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        GameStatus = (board[0][2] == 'X') ? AI_WIN : HUMAN_WIN;
    // проверка на ничью
    GameStatus = (GameStatus == -1000) ? DRAW : GameStatus;

    return GameStatus;
}

void get_moves(char **board, int *moves, int *num_moves)
{
    *num_moves = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                moves[*num_moves] = i * BOARD_SIZE + j;
                (*num_moves)++;
            }
        }
}

void apply_move(char **board, int move, char player)
{
    int i = move / 3;
    int j = move % 3;
    board[i][j] = player;
}

void undo_move(char **board, int move)
{
    int i = move / 3;
    int j = move % 3;
    board[i][j] = ' ';
}