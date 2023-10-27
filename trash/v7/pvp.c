#include "general.h"

char **table(int command)
{
    static char **board = NULL;
    if (command == CREATE)
    {
        board = (char **)calloc(BOARD_SIZE, sizeof(char *));
        if (board == NULL)
        {
            printf("No memory has been allocated! Exit..\n");
            exit(0);
        }
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            board[i] = (char *)calloc(BOARD_SIZE, sizeof(char));
            if (board[i] == NULL)
            {
                printf("No memory has been allocated! Exit..\n");
                exit(0);
            }
            for (int j = 0; j < BOARD_SIZE; j++)
                board[i][j] = EMPTY_SPACE;
        }
    }
    else if (command == DELETE)
    {
        for (int i = 0; i < BOARD_SIZE; i++)
            free(board[i]);
        free(board);
        board = NULL;
    }
    return board;
}

void initialize_board(char **board)
{
    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++)
            board[x][y] = EMPTY_SPACE;
}

int input_pvp(char **board)
{
    static int queue = 0;
    int x, y;
    printf("%c, enter the coordinates of the cell: ", ((queue) % 2 == 0) ? 'X' : 'O');
    if (scanf("%d", &x) != 1 || x < 1 || x > BOARD_SIZE)
    {
        if (x == EXIT)
            return EXIT;
        else
            printf("Invalid input. Please try again.\n");
    }
    else if (scanf("%d", &y) != 1 || y < 1 || y > BOARD_SIZE || board[x - 1][y - 1] != EMPTY_SPACE)
        printf("Invalid input. Please try again.\n");
    else
        board[x - 1][y - 1] = ((queue++) % 2 == 0) ? 'X' : 'O';
    return PVP;
}

int check_game_state(char **board)
{
    // Check for draw
    int GameStatus = EXIT;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == EMPTY_SPACE)
                GameStatus = ONGOING;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
        if (board[i][0] != EMPTY_SPACE && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            GameStatus = (board[i][0] == 'X') ? X_WON : O_WON;

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++)
        if (board[0][j] != EMPTY_SPACE && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            GameStatus = (board[0][j] == 'X') ? X_WON : O_WON;

    // Check diagonals
    if (board[0][0] != EMPTY_SPACE && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        GameStatus = (board[0][0] == 'X') ? X_WON : O_WON;

    if (board[0][2] != EMPTY_SPACE && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        GameStatus = (board[0][2] == 'X') ? X_WON : O_WON;

    GameStatus = (GameStatus == EXIT) ? NOBODY : GameStatus; // проверка на ничью

    return GameStatus;
}