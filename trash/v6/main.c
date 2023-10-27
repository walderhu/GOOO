#include "general.h"

int main()
{
    int status = lobby();
    char **board = creat_del_board(CREATE);
    initialize_board(board);
    while (!check_game_state(board))
    {
        if ((status == PVP) ? input(board) == EXIT : input_pve(board) == EXIT)
        {
            status = EXIT;
            printf("Exit...\n");
            break;
        }
        draw_board(board);
    }
    if (status != EXIT)
        won(board, status);
    creat_del_board(DELETE);
    return 0;
}

int lobby()
{
    system("clear");
    printf("\t\t\tTIC TAC TOE\n");

    printf("Select the game mode:\n 1. Player 1 vs Player 2\n 2. Player vs AI\n-1.To exit\nAnswer: ");
    float Answer;
    while (1)
        if (scanf("%f", &Answer) != 1 || Answer != (int)Answer || getchar() != '\n' || Answer == 0 || Answer < -1 || Answer > 2)
            printf("Invalid input, try again!\nAnswer: ");
        else
            break;

    system("clear");
    if (Answer == 1)
        printf("The Player vs player mode is selected\n");
    else if (Answer == 2)
        printf("The Player vs AI mode is selected\n");

    if (Answer != -1)
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
            for (int y = 0; y < BOARD_SIZE; y++)
                (y == BOARD_SIZE - 1) ? printf("|%d %d|\n", x + 1, y + 1) : printf("|%d %d", x + 1, y + 1);
            if (x == BOARD_SIZE - 1)
                printf(" ----------- \n");
        }

    return (int)Answer;
}

void draw_board(char **board)
{
    // system("clear");
    for (size_t x = 0; x < BOARD_SIZE; x++)
    {
        x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
        for (size_t y = 0; y < BOARD_SIZE; y++)
            (y == BOARD_SIZE - 1) ? printf("| %c |\n", board[x][y]) : printf("| %c ", board[x][y]);
        if (x == BOARD_SIZE - 1)
            printf(" ----------- \n");
    }
}

void won(char **board, int status)
{
    switch (status)
    {
    case PVE:
        switch (evaluate(board))
        {
        case HUMAN_WIN:
            printf("AI won!\n");
            break;
        case AI_WIN:
            printf("Human won!\n");
            break;
        case DRAW:
            printf("Draw!\n");
            break;
        }
        break;

    case PVP:
        switch (check_game_state(board))
        {
        case X_WON:
            printf("X won!\n");
            break;
        case O_WON:
            printf("O won!\n");
            break;
        case NOBODY:
            printf("Draw!\n");
            break;
        }
        break;
    }
}
