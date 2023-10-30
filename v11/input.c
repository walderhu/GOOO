#include "general.h"
int get_user_input(int num_options, ...)
{
    while (1)
    {
        float answer;
        va_list options;
        va_start(options, num_options);

        printf("Answer: ");
        if (scanf("%f", &answer) && answer == (int)answer && (getchar() == '\n' || getchar() == ' '))
        {
            for (int i = 0; i < num_options; i++)
                if (answer == va_arg(options, int))
                {
                    va_end(options);
                    return answer;
                }
        }
        else
            while (getchar() != '\n')
                ;
        printf("\033[1A"); // Move the cursor up one line
        printf("\033[2K"); // Clear the current line
        printf("Invalid input, try again!\n");
        sleep(1);
        printf("\033[1A"); // Move the cursor up one line
        printf("\033[2K"); // Clear the current line
        va_end(options);
    }
}

int lobby(char **board, GAME_t *status)
{
    status->menu = 0;
    system("clear");
    printf("\t\t\tTIC TAC TOE\n");
    printf("Select the game mode:\n %d. Player 1 vs Player 2\n %d. Player vs AI\n%d. To exit\n", PVP, PVE, EXIT);
    float answer = get_user_input(3, PVP, PVE, EXIT);
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

int input_pve(char **board)
{
    static int queue = 0;
    static float x, y;
    if (queue % 2 == 0)
    {
        printf("%c, select a cell\n", ((queue) % 2 == 0) ? 'X' : 'O');
        do
        {
            x = get_user_input(4, EXIT, 1, 2, 3);
            if (x == EXIT)
                return EXIT;

            y = get_user_input(3, 1, 2, 3);

        } while (board[(int)x - 1][(int)y - 1] != EMPTY_SPACE);

        board[(int)x - 1][(int)y - 1] = ((queue) % 2 == 0) ? 'X' : 'O';
        system("clear");
    }
    else
    {
        int best_move = -1;
        minimax(board, 'O', 0, &best_move);
        if (best_move == -1)
        {
            printf("AI couldn't find the best move\n");
            return PVE;
        }
        int i = best_move / BOARD_SIZE;
        int j = best_move % BOARD_SIZE;
        board[i][j] = ((queue) % 2 == 0) ? 'X' : 'O';
        system("clear");
    }
    queue++;
    return PVE;
}

int input_pvp(char **board)
{
    static int queue = 0;
    float x, y;
    printf("%c, select a cell\n", ((queue) % 2 == 0) ? 'X' : 'O');
    do
    {
        x = get_user_input(4, EXIT, 1, 2, 3);

        if (x == EXIT)
            return EXIT;

        y = get_user_input(3, 1, 2, 3);

    } while (board[(int)x - 1][(int)y - 1] != EMPTY_SPACE);

    board[(int)x - 1][(int)y - 1] = ((queue) % 2 == 0) ? 'X' : 'O';
    queue++;
    system("clear");
    return PVP;
}

int menu()
{
    system("clear");
    printf("Select an action:\n");
    printf(" %d. Continue the game\n", CONTINUE_GAME);
    printf(" %d. Start over\n", START_OVER);
    printf(" %d. Exit to the lobby\n", EXIT_TO_LOBBY);
    printf(" %d. Exit the game\n", EXIT_THE_GAME);

    float answer = get_user_input(4, CONTINUE_GAME, START_OVER, EXIT_TO_LOBBY, EXIT_THE_GAME);
    system("clear");
    return answer;
}

int input(char **board, GAME_t *status)
{
    if (status->game == PVP)
    {
        status->tmp = input_pvp(board);
        if (status->tmp == MENU)
            status->menu = status->tmp;
        else
            status->game = status->tmp;
    }
    else if (status->game == PVE)
    {
        status->tmp = input_pve(board);
        if (status->tmp == MENU)
            status->menu = status->tmp;
        else
            status->game = status->tmp;
    }
    else
        return status->tmp;

    if (status->menu == MENU)
        status->menu = menu();

    if (status->menu == START_OVER)
    {
        initialize_board(board);
        status->menu = 0;
    }
}