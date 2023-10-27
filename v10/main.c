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

        if (!(status.menu == EXIT_TO_LOBBY || EXIT_THE_GAME))
            won(board, status);
    }
    table(DELETE);
    return 0;
}

int lobby(char **board, GAME_t *status)
{
    status->menu = 0;
    system("clear");
    printf("\t\t\tTIC TAC TOE\n");

    printf("Select the game mode:\n %d. Player 1 vs Player 2\n %d. Player vs AI\n%d. To exit\n", PVP, PVE, EXIT);
    //
    float answer;
    while (TRUE)
    {
        printf("Answer: ");
        if (scanf("%f", &answer) && (answer == EXIT || answer == PVE || answer == PVP))
            break;
        // Clear input buffer
        while (getchar() != '\n')
            ;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //
        //      // пасхалка)))
        //      // printf("HHEEEEEEY");
        // printf("\033[2K\r"); // Clear the current line
        //
        static int a = 0;
        if ((a++) == 0)
            printf("\n");
            
        for (int i = 0; i < 2; i++)
        {
            printf("\033[2K"); // Clear the current line
            printf("\033[1A"); // Move the cursor up one line
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        printf("Invalid input, try again!\n");
    }
    //
    system("clear");
    if (answer == PVP)
        printf("The Player vs player mode is selected\n");
    else if (answer == PVE)
        printf("The Player vs AI mode is selected\n");
    else
    {
        status->game = EXIT;
        return status->game;
    }
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
        for (int y = 0; y < BOARD_SIZE; y++)
            (y == BOARD_SIZE - 1) ? printf("|%d %d|\n", x + 1, y + 1) : printf("|%d %d", x + 1, y + 1);
        if (x == BOARD_SIZE - 1)
            printf(" ----------- \n");
    }
    status->game = answer;
    initialize_board(board);

    return status->game;
}

void draw_board(char **board, GAME_t *status)
{
    // system("clear");
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

void won(char **board, GAME_t status)
{
    switch (status.game)
    {
    case EXIT:
        break;
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