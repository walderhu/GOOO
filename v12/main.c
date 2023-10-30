#include "general.h"

int main()
{
    GAME_t status = {EXIT_TO_LOBBY};
    char board[BOARD_SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    while (status.menu == EXIT_TO_LOBBY && lobby(board, &status) != EXIT)
        while (!check_game_state(board) && (input(board, &status) != MENU))
            if (status.menu == EXIT_THE_GAME || status.menu == EXIT_TO_LOBBY)
                break;
            else
                draw_board(board, &status);
    return 0;
}

void draw_board(char *board, GAME_t *status)
{
    printf("   %s mode\n", (status->game == PVP) ? "PVP" : "PVE");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (i % 3 == 0)
            printf(" ----------- \n");
        printf("| %c ", board[i]);
        if (i % 3 == 2)
            printf("|\n");
    }
    printf(" ----------- \n");
}

void initialize_board(char *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
        board[i] = ' ';
}

int check_game_state(char *board)
{
    // Check for draw
    int GameStatus = EXIT;
    for (int i = 0; i < BOARD_SIZE; i++)
        if (board[i] != 'X' && board[i] != 'O')
            GameStatus = ONGOING;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i += 3)
        if (board[i] != ' ' && board[i] == board[i + 1] && board[i + 1] == board[i + 2])
            GameStatus = (board[i] == 'X') ? X_WON : O_WON;

    // Check columns
    for (int j = 0; j < 3; j++)
        if (board[j] != ' ' && board[j] == board[j + 3] && board[j + 3] == board[j + 6])
            GameStatus = (board[j] == 'X') ? X_WON : O_WON;

    // Check diagonals
    if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8])
        GameStatus = (board[0] == 'X') ? X_WON : O_WON;

    if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6])
        GameStatus = (board[2] == 'X') ? X_WON : O_WON;

    GameStatus = (GameStatus == EXIT) ? NOBODY : GameStatus; // Check for draw

    return GameStatus;
}
