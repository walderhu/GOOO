#include "general.h"

int main()
{
    int status;
    char **board = table(CREATE);
    do
    {
        status = lobby();
        if (status == EXIT)
            break;
        initialize_board(board);
        while (!check_game_state(board))
        {
            if (status == PVP)
                status = input_pvp(board);
            else if (status == PVE)
                status = input_pve(board);
            else
                break;
            draw_board(board);
        }
        won(board, status);
    //
        printf("Do you want to start over?\n1. Yes\n2. No\nAnswer: ");
        /*
        Вы  хотите выйти?
        1. Нет, продолжить игру
        2. Начать заново
        3. Выйти в главное меню
        4. Выйти из игры
        */
        scanf("%d", &status);
    } while (status == AGAIN);
    // переработать этот участок кода
    table(DELETE);
    return 0;
}

int lobby()
{
    system("clear");
    printf("\t\t\tTIC TAC TOE\n");

    printf("Select the game mode:\n %d. Player 1 vs Player 2\n %d. Player vs AI\n%d. To exit\n", PVP, PVE, EXIT);
    //
    float answer;
    while (TRUE)
    {
        printf("Answer: ");
        if (scanf("%f", &answer) == TRUE && answer == (int)answer)
            if (answer == EXIT || answer == PVE || answer == PVP)
                break;
        // Clear input buffer
        while (getchar() != '\n')
            ;
        printf("Invalid input, try again!\n");
    }
    //
    // system("clear");
    if (answer == PVP)
        printf("The Player vs player mode is selected\n");
    else if (answer == PVE)
        printf("The Player vs AI mode is selected\n");
    else
        return EXIT;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
        for (int y = 0; y < BOARD_SIZE; y++)
            (y == BOARD_SIZE - 1) ? printf("|%d %d|\n", x + 1, y + 1) : printf("|%d %d", x + 1, y + 1);
        if (x == BOARD_SIZE - 1)
            printf(" ----------- \n");
    }
    return answer;
}

void draw_board(char **board)
{
    // system("clear");
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
        for (int y = 0; y < BOARD_SIZE; y++)
            (y == BOARD_SIZE - 1) ? printf("| %c |\n", board[x][y]) : printf("| %c ", board[x][y]);
        if (x == BOARD_SIZE - 1)
            printf(" ----------- \n");
    }
}

void won(char **board, int status)
{
    switch (status)
    {
    case EXIT:
        printf("Exit...\n");
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