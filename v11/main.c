#include "general.h"

int main()
{
    GAME_t status = {EXIT_TO_LOBBY};
    char **board = table(CREATE);
    while (status.menu == EXIT_TO_LOBBY && lobby(board, &status) != EXIT)
    {
        while (!check_game_state(board) && (input(board, &status) != MENU))
            if (status.menu == EXIT_THE_GAME || status.menu == EXIT_TO_LOBBY)
                break;
            else
                draw_board(board, &status);

        if (status.menu != EXIT_TO_LOBBY || status.menu != EXIT_THE_GAME)
        {
            won(board, &status);
        }
    }
    table(DELETE);
    return 0;
}


void draw_board(char **board, GAME_t *status)
{
    printf("   %s mode\n", (status->game == PVP) ? "PVP" : "PVE");

    for (int x = 0; x < BOARD_SIZE; x++)
    {
        x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
        for (int y = 0; y < BOARD_SIZE; y++)
            (y == BOARD_SIZE - 1) ? printf("| %c |\n", board[x][y]) : printf("| %c ", board[x][y]);
        if (x == BOARD_SIZE - 1)
            printf(" ----------- \n");
    }
}

void won(char **board, GAME_t *status)
{
    switch (status->game)
    {
    case PVE:
        switch (evaluate(board))
        {
        case HUMAN_WIN:
            printf("   AI won!\n");
            break;
        case AI_WIN:
            printf("   Human won!\n");
            break;
        // case DRAW:
            // printf("Draw!\n");
            // break;
        }
        break;

    case PVP:
        switch (check_game_state(board))
        {
        case X_WON:
            printf("   X won!\n");
            break;
        case O_WON:
            printf("   O won!\n");
            break;
        // case NOBODY:
            // printf("Draw!\n");
            // break;
        }
        break;
    }
    sleep(1);
    // status->menu = menu();
    // status->menu = EXIT_TO_LOBBY;
}